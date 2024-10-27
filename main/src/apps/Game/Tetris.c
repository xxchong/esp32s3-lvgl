#include "sys.h"
#include <time.h>
#include <stdio.h>  // 添加这行
#include <stdlib.h> // 添加这行
#include "esp_attr.h"
#include "esp_heap_caps.h"

#define CANVAS_WIDTH 220
#define CANVAS_HEIGHT 260
/* 创建一个画布的缓冲区 */
static lv_color_t *cbuf; // 使用 LV_IMG_CF_TRUE_COLOR需要这样定义
// static lv_color_t next_block_canvas_cbuf[(32 * 70) / 8 * 50];    // 使用 LV_IMG_CF_TRUE_COLOR需要这样定义

#define BLOCK_SIZE 10
#define GRID_WIDTH 24 // 游戏网格的宽高
#define GRID_HEIGHT 28

static lv_obj_t *create_game_canvas(lv_obj_t *parent);      // 创建用于绘制方块的画布
static void draw_next_block(void);                          // 绘制下一个方块
static void init_game(void);                                // 初始化游戏状态
static void rotate_piece_times(int piece[4][4], int times); // 将方块旋转随机
static bool generate_new_piece(void);                       // 生成新的方块
static void draw_game(void);                                // 绘制当前游戏状态
static bool check_collision(void);                          // 检查当前方块是否与其他方块或边界发生碰撞
static void fix_piece(void);                                // 将当前方块固定到游戏网格中
static void clear_lines(void);                              // 清除已填满的行并计算得分
static bool move_down_and_fix(void);                        // 尝试将方块向下移动，如果不能则固定方块
static bool is_Square_block(void);                          // 检查当前方块是否为田字形（方形）
static void rotate_piece(void);                             // 旋转当前方块
static void game_loop(lv_timer_t *timer);                   // 游戏主循环，由定时器定期调用
static void msgbox_event_cb(lv_event_t *e);                 // 处理消息框事件的回调函数
static void reset_game_state(void);                         // 重置游戏状态到初始状态
static void Stop_Game(void);                                // 停止游戏，清理资源
static bool generate_new_piece(void);

// 游戏状态
typedef struct
{
    int grid[GRID_HEIGHT][GRID_WIDTH]; // 游戏的主网格，代表整个游戏区域。21x10个方格
    int current_piece[4][4];           // 这个数组代表当前正在移动的方块。
    int next_piece[4][4];              // 这个数组代表下一个的方块。
    int current_x;                     // 当前方块的x坐标
    int current_y;                     // 当前方块的y坐标
    int score;                         // 分数
    int level;                         // 关卡
    int speed;                         // 速度
    bool is_game_over;                 // 游戏是否结束
    bool first_piece;                  // 是否为第一个方块
    int lines_cleared;                 // 已消除的行数
    int combo;                         // 连续消除的次数
    lv_color_t current_color;          // 当前方块的颜色
    lv_color_t next_color;             // 下一个方块的颜色
} GameState;

typedef struct
{
    lv_obj_t *game_canvas; // 画布
    lv_timer_t *game_timer;
    lv_draw_rect_dsc_t game_rect_dsc;      // 小方块
    lv_draw_rect_dsc_t game_next_rect_dsc; // 小方块
    lv_obj_t *game_next_block_canvas;      // 画布

} lv_game_t;
static lv_game_t *lv_game;
static GameState game_state;

// 方块形状定义
const int SHAPES[7][4][4] = {
    // 其他默认0 7个四行四列的二位数组
    {{1, 1, 1, 1}},         // I
    {{1, 1}, {1, 1}},       // O
    {{1, 1, 1}, {0, 1, 0}}, // T
    {{1, 1, 1}, {1, 0, 0}}, // L
    {{1, 1, 1}, {0, 0, 1}}, // J
    {{1, 1, 0}, {0, 1, 1}}, // S
    {{0, 1, 1}, {1, 1, 0}}  // Z
};

// extern lv_indev_t *indev ;

static bool Pause_Game = false;

static void draw_next_block(void)
{
    if (game_state.is_game_over)
        return;
    lv_canvas_fill_bg(lv_game->game_next_block_canvas, lv_color_black(), LV_OPA_COVER);
    lv_draw_rect_dsc_init(&lv_game->game_next_rect_dsc);
    lv_game->game_next_rect_dsc.bg_color = lv_color_white();
    lv_game->game_next_rect_dsc.border_width = 1;
    lv_game->game_next_rect_dsc.border_color = lv_color_black();
    lv_game->game_next_rect_dsc.radius = 1;
    int block_size = 10; // 方块大小
    // 计算实际的方块尺寸
    int actual_width = 0, actual_height = 0;
    int min_x = 3, min_y = 3;
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (game_state.next_piece[y][x])
            {
                actual_width = (x + 1 > actual_width) ? x + 1 : actual_width;
                actual_height = (y + 1 > actual_height) ? y + 1 : actual_height;
                min_x = (x < min_x) ? x : min_x;
                min_y = (y < min_y) ? y : min_y;
            }
        }
    }
    actual_width -= min_x;
    actual_height -= min_y;
    // 计算居中偏移
    int offset_x = (96 - actual_width * block_size) / 2;
    int offset_y = (46 - actual_height * block_size) / 2;

    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (game_state.next_piece[y][x])
            {
                lv_coord_t rect_x = offset_x + (x - min_x) * block_size;
                lv_coord_t rect_y = offset_y + (y - min_y) * block_size;
                lv_canvas_draw_rect(lv_game->game_next_block_canvas, rect_x, rect_y, block_size, block_size, &lv_game->game_next_rect_dsc);
            }
        }
    }
    // 强制重绘
    lv_obj_invalidate(lv_game->game_next_block_canvas);
}

static lv_obj_t *create_game_canvas(lv_obj_t *parent)
{
    cbuf = heap_caps_malloc((32 * CANVAS_WIDTH) / 8 * CANVAS_HEIGHT * sizeof(lv_color_t), MALLOC_CAP_SPIRAM);
    if (cbuf == NULL)
    {
        // 处理内存分配失败
    }
    lv_game->game_canvas = lv_canvas_create(parent);
    lv_obj_set_style_border_color(lv_game->game_canvas, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(lv_game->game_canvas, 1, LV_PART_MAIN);
    lv_obj_set_style_outline_width(lv_game->game_canvas, 0, LV_PART_MAIN);
    lv_obj_center(lv_game->game_canvas);
    lv_canvas_set_buffer(lv_game->game_canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
    return lv_game->game_canvas;
}

// 初始化游戏
static void init_game(void)
{
    printf("正在初始化游戏...\n");

    printf("清空游戏网格...\n");
    memset(game_state.grid, 0, sizeof(game_state.grid));

    printf("初始化游戏参数...\n");
    game_state.score = 0;
    game_state.level = 1;
    game_state.speed = 500;
    game_state.is_game_over = false;
    game_state.first_piece = true;
    game_state.lines_cleared = 0;
    game_state.combo = 0;

    printf("生成新方块...\n");
    if (!generate_new_piece())
    {
        printf("生成新方块失败\n");
        return;
    }

    printf("游戏初始化完成\n");
}

// 将随机生成的方块旋转
static void rotate_piece_times(int piece[4][4], int times)
{
    for (int t = 0; t < times; t++)
    {
        int temp[4][4] = {0};
        for (int y = 0; y < 4; y++)
        {
            for (int x = 0; x < 4; x++)
            {
                temp[x][3 - y] = piece[y][x];
            }
        }
        memcpy(piece, temp, sizeof(temp));
    }
}
// 生成新方块
static bool generate_new_piece(void)
{
    // printf("正在生成新方块...\n");

    // // 检查 SHAPES 数组
    // if (SHAPES == NULL)
    // {
    //     // printf("错误：SHAPES 数组未定义\n");
    //     return false;
    // }

    game_state.current_x = GRID_WIDTH / 2 - 2;
    game_state.current_y = 0;

    // 使用当前时间作为随机数种子
    srand((unsigned int)time(NULL));

    int shape = rand() % 7;
    int rotations = rand() % 4;

    // printf("选择形状：%d，旋转次数：%d\n", shape, rotations);

    if (game_state.first_piece)
    {
        memcpy(game_state.current_piece, SHAPES[shape], sizeof(game_state.current_piece));
        rotate_piece_times(game_state.current_piece, rotations);
        game_state.current_color = lv_color_make(rand() % 256, rand() % 256, rand() % 256);

        shape = rand() % 7;
        rotations = rand() % 4;
        memcpy(game_state.next_piece, SHAPES[shape], sizeof(game_state.next_piece));
        rotate_piece_times(game_state.next_piece, rotations);
        game_state.next_color = lv_color_make(rand() % 256, rand() % 256, rand() % 256);

        game_state.first_piece = false;
    }
    else
    {
        memcpy(game_state.current_piece, game_state.next_piece, sizeof(game_state.current_piece));
        game_state.current_color = game_state.next_color;

        shape = rand() % 7;
        rotations = rand() % 4;
        memcpy(game_state.next_piece, SHAPES[shape], sizeof(game_state.next_piece));
        rotate_piece_times(game_state.next_piece, rotations);
        game_state.next_color = lv_color_make(rand() % 256, rand() % 256, rand() % 256);
    }

    if (check_collision())
    {
        game_state.is_game_over = true;
        // printf("新方块生成时发生碰撞，游戏结束\n");
        return false;
    }

    // 更新下一个方块的显示
    // draw_next_block();

    // printf("新方块生成成功\n");
    return true;
}

// 绘制游戏状态
static void draw_game(void)
{
    lv_canvas_fill_bg(lv_game->game_canvas, lv_color_black(), LV_OPA_COVER);
    lv_draw_rect_dsc_init(&lv_game->game_rect_dsc);
    lv_game->game_rect_dsc.bg_color = lv_color_white(); // 红色
    lv_game->game_rect_dsc.border_width = 1;
    lv_game->game_rect_dsc.border_color = lv_color_black(); // 红色
    lv_game->game_rect_dsc.radius = 1;

    // 绘制已固定的方块
    for (int y = 0; y < GRID_HEIGHT; y++)
    { // 改为 GRID_HEIGHT
        for (int x = 0; x < GRID_WIDTH; x++)
        { // 改为 GRID_WIDTH
            if (game_state.grid[y][x])
            {
                lv_canvas_draw_rect(lv_game->game_canvas,
                                    x * BLOCK_SIZE,
                                    y * BLOCK_SIZE,
                                    BLOCK_SIZE,
                                    BLOCK_SIZE,
                                    &lv_game->game_rect_dsc);
            }
        }
    }
    // 绘制当前方块
    lv_game->game_rect_dsc.bg_color = game_state.current_color;
    lv_game->game_rect_dsc.border_color = lv_color_darken(game_state.current_color, LV_OPA_COVER);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (game_state.current_piece[y][x])
            {
                lv_canvas_draw_rect(lv_game->game_canvas,
                                    (game_state.current_x + x) * BLOCK_SIZE,
                                    (game_state.current_y + y) * BLOCK_SIZE,
                                    BLOCK_SIZE,
                                    BLOCK_SIZE,
                                    &lv_game->game_rect_dsc);
            }
        }
    }
}

// 检查碰撞
static bool check_collision(void)
{
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (game_state.current_piece[y][x])
            {
                int new_x = game_state.current_x + x;
                int new_y = game_state.current_y + y;                           // new_x < 0：方块超出左边界
                if (new_x < 0 || new_x >= GRID_WIDTH || new_y >= GRID_HEIGHT || // new_x >= GRID_WIDTH：方块超出右边界
                    (new_y >= 0 && game_state.grid[new_y][new_x]))
                {                // new_y >= GRID_HEIGHT：方块超出底部边界
                    return true; // new_y >= 0 && game.grid[new_y][new_x]：方块与已固定的方块重叠
                }
            }
        }
    }
    return false;
}

// 固定当前方块
// 方块到达底部
// 方块碰到其他已固定的方块
static void fix_piece(void)
{
    for (int y = 0; y < 4; y++)
    { // 遍历当前方块的 4x4 数组
        for (int x = 0; x < 4; x++)
        {
            if (game_state.current_piece[y][x])
            {                                                                            // 4x4 数组中的每个位置，检查是否有方块（值为1）
                game_state.grid[game_state.current_y + y][game_state.current_x + x] = 1; // 如果该位置有方块，则将其固定到游戏主网格中
            }
        }
    }
}

// 消除已满的行
static void clear_lines(void)
{
    int lines_cleared = 0;
    for (int y = GRID_HEIGHT - 1; y >= 0; y--)
    {
        bool line_full = true;
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (!game_state.grid[y][x])
            {
                line_full = false;
                break;
            }
        }
        if (line_full)
        {
            lines_cleared++;
            for (int yy = y; yy > 0; yy--)
            {
                memcpy(game_state.grid[yy], game_state.grid[yy - 1], sizeof(game_state.grid[0]));
            }
            memset(game_state.grid[0], 0, sizeof(game_state.grid[0]));
            y++; // 重新检查当前行
        }
    }
    // 更新总消除行数
    game_state.lines_cleared += lines_cleared;
    // 计算基础分数
    int base_score = 0;
    switch (lines_cleared)
    {
    case 1:
        base_score = 100;
        break;
    case 2:
        base_score = 300;
        break;
    case 3:
        base_score = 500;
        break;
    case 4:
        base_score = 800;
        break;
    }
    // 应用等级倍数和连击奖励
    int level_multiplier = game_state.level;
    int combo_bonus = (game_state.combo > 1) ? game_state.combo * 50 : 0;
    game_state.score += (base_score * level_multiplier) + combo_bonus;
    // 更新连击次数
    if (lines_cleared > 0)
    {
        game_state.combo++;
    }
    else
    {
        game_state.combo = 0;
    }
    // 检查是否升级
    if (game_state.lines_cleared / 10 > game_state.level - 1)
    {
        game_state.level++;
        game_state.speed = (int)(game_state.speed * 0.9); // 加快10%
        lv_timer_set_period(lv_game->game_timer, game_state.speed);
    }
}

static bool move_down_and_fix(void)
{
    game_state.current_y++;
    if (check_collision())
    {
        game_state.current_y--;
        fix_piece();
        clear_lines();
        //        draw_next_blocK();
        // 检查是否游戏结束
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (game_state.grid[0][x] || game_state.grid[1][x])
            {
                game_state.is_game_over = true;
                return false;
            }
        }
        return generate_new_piece(); // 返回生成新方块的结果
    }
    return true; // 可以继续游戏
}

// 定义一个函数来检查当前方块是否为田字形
static bool is_Square_block(void)
{
    return game_state.current_piece[0][0] == 1 && game_state.current_piece[0][1] == 1 &&
           game_state.current_piece[1][0] == 1 && game_state.current_piece[1][1] == 1;
}

static void rotate_piece(void)
{
    // 如果是田字形，直接返回
    if (is_Square_block())
    {
        return;
    }
    int temp[4][4] = {0};
    int size = 0;
    // 确定当前方块的实际大小
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (game_state.current_piece[y][x])
            {
                size = (x > size) ? x : size;
                size = (y > size) ? y : size;
            }
        }
    }
    size++;

    // 复制并旋转
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            temp[x][size - 1 - y] = game_state.current_piece[y][x];
        }
    }
    // 检查旋转后是否发生碰撞
    bool can_rotate = true;
    for (int y = 0; y < size; y++)
    {
        for (int x = 0; x < size; x++)
        {
            if (temp[y][x])
            {
                int new_x = game_state.current_x + x;
                int new_y = game_state.current_y + y;
                if (new_x < 0 || new_x >= GRID_WIDTH || new_y >= GRID_HEIGHT ||
                    (new_y >= 0 && game_state.grid[new_y][new_x]))
                {
                    can_rotate = false;
                    break;
                }
            }
        }
        if (!can_rotate)
            break;
    }
    // 如果可以旋转，更新方块
    if (can_rotate)
    {
        memcpy(game_state.current_piece, temp, sizeof(game_state.current_piece));
    }
}

// 在游戏主循环
static void game_loop(lv_timer_t *timer)
{
    if (game_state.is_game_over)
    {
        // 游戏结束
        lv_timer_del(lv_game->game_timer);
        printf("game_state over\n");
        return;
    }
    if (!move_down_and_fix())
    {
        game_state.is_game_over = true;
        return;
    }
    draw_game();
}

// 键盘事件处理
static void keyboard_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_timer_t *timer = lv_event_get_user_data(e);

    if (code == LV_EVENT_KEY)
    {
        uint32_t key = lv_event_get_key(e);

        if (!game_state.is_game_over)
        {
            switch (key)
            {
            case LV_KEY_LEFT:
                game_state.current_x--;
                if (check_collision())
                    game_state.current_x++;
                break;
            case LV_KEY_RIGHT:
                game_state.current_x++;
                if (check_collision())
                    game_state.current_x--;
                break;
            case LV_KEY_DOWN:
                // 快速下落
                for (int i = 0; i < 3 && !game_state.is_game_over; i++)
                {
                    if (!move_down_and_fix())
                    {
                        game_state.is_game_over = true;
                        break;
                    }
                }
                break;
            case LV_KEY_ENTER:
                rotate_piece();
                break;
            case LV_KEY_ESC: // ESC 暂停以及退出操作
                printf("暂停中\n");

                break;
            }
            if (!game_state.is_game_over)
                draw_game();
        }
        else
        {
        }
    }
}

// 重置游戏状态
static void reset_game_state(void)
{
    printf("正在重置游戏状态...\n");
    memset(&game_state, 0, sizeof(GameState));
    game_state.level = 1;
    game_state.speed = 500;
    game_state.is_game_over = false;
    game_state.score = 0;
    game_state.current_x = GRID_WIDTH / 2 - 2;
    game_state.current_y = 0;
    game_state.lines_cleared = 0;
    game_state.combo = 0;
    Pause_Game = false;
}
static void Stop_Game(void)
{
    if (lv_game->game_timer)
    {
        printf("Deleting game_timer\n");
        lv_timer_del(lv_game->game_timer);
        lv_game->game_timer = NULL;
    }
    // 先删除子对象
    if (lv_game->game_canvas && lv_obj_is_valid(lv_game->game_canvas))
    {
        printf("Deleting game.canvas\n");
        lv_obj_del(lv_game->game_canvas);
        lv_game->game_canvas = NULL;
    }
    if (lv_game->game_next_block_canvas && lv_obj_is_valid(lv_game->game_next_block_canvas))
    {
        printf("Deleting next_block_canvas\n");
        lv_obj_del(lv_game->game_next_block_canvas);
        lv_game->game_next_block_canvas = NULL;
    }
}

static lv_obj_t *create_next_block_canvas(lv_obj_t *parent)
{
    // lv_game->game_next_block_canvas = lv_canvas_create(parent);
    // lv_canvas_set_buffer(lv_game->game_next_block_canvas, next_block_canvas_cbuf, 70, 50, LV_IMG_CF_TRUE_COLOR);

    // lv_canvas_fill_bg(lv_game->game_next_block_canvas, lv_color_black(), LV_OPA_COVER);

    // return lv_game->game_next_block_canvas;
    return NULL;
}

void tetris_start_game(lv_obj_t *parent, lv_group_t *group)
{
    if (lv_game == NULL)
    {
        lv_game = (lv_game_t *)malloc(sizeof(lv_game_t));
        if (lv_game == NULL)
        {
            // 处理内存分配失败的情况
            printf("Failed to allocate memory for game_app\n");
            return;
        }
        // 初始化成员变量
        lv_game->game_canvas = NULL;
        lv_game->game_timer = NULL;
        lv_game->game_next_block_canvas = NULL;
    }

    lv_obj_align(create_game_canvas(parent), LV_ALIGN_BOTTOM_MID, 0, -8);

    // lv_obj_align_to(create_next_block_canvas(parent), lv_game->game_canvas, LV_ALIGN_OUT_TOP_MID, 0, -5);

    init_game();
    if (lv_game->game_timer)
    {
        lv_timer_del(lv_game->game_timer);
    }
    lv_game->game_timer = lv_timer_create(game_loop, game_state.speed, NULL);
    lv_obj_add_event_cb(parent, keyboard_event_cb, LV_EVENT_KEY, NULL);
    lv_group_add_obj(group, parent);
    lv_timer_reset(lv_game->game_timer);
}
