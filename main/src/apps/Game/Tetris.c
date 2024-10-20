#include "sys.h"
#include "esp_attr.h"
#include "esp_heap_caps.h"

#define CANVAS_WIDTH 120
#define CANVAS_HEIGHT 200
/* 创建一个画布的缓冲区 */
static lv_color_t cbuf[(32 * CANVAS_WIDTH) / 8 * CANVAS_HEIGHT]; // 使用 LV_IMG_CF_TRUE_COLOR需要这样定义
#define BLOCK_SIZE 10
#define GRID_WIDTH 12 // 游戏网格的宽高
#define GRID_HEIGHT 20

static void create_blocKs_canvas(lv_obj_t *parent);         // 创建用于绘制方块的画布
static void draw_next_blocK(void);                          // 绘制下一个方块
static void init_next_blocK(void);                          // 初始化下一个方块的显示
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

// 游戏状态
typedef struct
{
    lv_obj_t *canvas;                  // 画布
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

static lv_timer_t *game_timer;
// extern lv_indev_t *indev ;
static lv_obj_t *next_block__win;
static lv_obj_t *next_block_canvas;
static lv_obj_t *root;
static lv_obj_t *game_msgbox;
static lv_obj_t *exit_msgbox;
static lv_obj_t *game_win;
static lv_obj_t *info_win;
static lv_obj_t *btn_exit;
static lv_obj_t *btn_con;
static lv_draw_rect_dsc_t dsc_next_block;
static lv_draw_rect_dsc_t rect_dsc;
static lv_obj_t *new_game_mbox;
static lv_obj_t *btn_yes;
static lv_obj_t *btn_no;
static lv_style_t style_btn;
static lv_style_t style_btn_focused;
static bool generate_new_piece(void);
static bool Pause_Game = false;

static GameState game;

// static void draw_next_blocK(void)
// {
//     if(game.is_game_over) return;
//     lv_canvas_fill_bg(next_block_canvas, lv_color_black(), LV_OPA_COVER);
//     lv_canvas_fill_bg(next_block_canvas, lv_color_black(), LV_OPA_COVER);
//     lv_draw_rect_dsc_init(&dsc_next_block);
//     dsc_next_block.bg_color = lv_color_white();
//     dsc_next_block.border_width = 1;
//     dsc_next_block.border_color = lv_color_black();
//     dsc_next_block.radius = 0;
//     int block_size = 8;  // 方块大小
//     // 计算实际的方块尺寸
//     int actual_width = 0, actual_height = 0;
//     int min_x = 3, min_y = 3;
//     for (int y = 0; y < 4; y++) {
//         for (int x = 0; x < 4; x++) {
//             if (game.next_piece[y][x]) {
//                 actual_width = (x + 1 > actual_width) ? x + 1 : actual_width;
//                 actual_height = (y + 1 > actual_height) ? y + 1 : actual_height;
//                 min_x = (x < min_x) ? x : min_x;
//                 min_y = (y < min_y) ? y : min_y;
//             }
//         }
//     }
//     actual_width -= min_x;
//     actual_height -= min_y;
//     // 计算居中偏移
//     int offset_x = (96 - actual_width * block_size) / 2;
//     int offset_y = (46 - actual_height * block_size) / 2;

//     for (int y = 0; y < 4; y++)
//     {
//         for (int x = 0; x < 4; x++)
//         {
//             if (game.next_piece[y][x])
//             {
//                 lv_coord_t rect_x = offset_x + (x - min_x) * block_size;
//                 lv_coord_t rect_y = offset_y + (y - min_y) * block_size;
//                 lv_canvas_draw_rect(next_block_canvas, rect_x, rect_y, block_size, block_size, &dsc_next_block);
//             }
//         }
//     }
//     lv_canvas_finish_layer(next_block_canvas, &layer_next_block);
//     // 强制重绘
//     lv_obj_invalidate(next_block_canvas);
// }
// static void init_next_blocK(void)
//{
//    LV_DRAW_BUF_DEFINE(draw_buf_next_block, 96, 46, LV_COLOR_FORMAT_ARGB8888);
//    next_block_canvas = lv_canvas_create(next_block__win);
//    lv_obj_set_style_border_color(next_block_canvas,lv_color_white(),LV_PART_MAIN);
//    lv_obj_set_style_border_width(next_block_canvas,2,LV_PART_MAIN);
//    lv_obj_set_style_outline_width(next_block_canvas,0,LV_PART_MAIN);
//    lv_obj_center(next_block_canvas);
//    lv_canvas_set_draw_buf(next_block_canvas, &draw_buf_next_block);//给画布设置内存空间
//
//}

static void create_blocks_canvas(lv_obj_t *parent)
{
    game.canvas = lv_canvas_create(parent);
    lv_obj_set_style_border_color(game.canvas, lv_color_white(), LV_PART_MAIN);
    lv_obj_set_style_border_width(game.canvas, 1, LV_PART_MAIN);
    lv_obj_set_style_outline_width(game.canvas, 0, LV_PART_MAIN);
    lv_obj_center(game.canvas);
    lv_canvas_set_buffer(game.canvas, cbuf, CANVAS_WIDTH, CANVAS_HEIGHT, LV_IMG_CF_TRUE_COLOR);
}

// 初始化游戏
static void init_game(void)
{
    printf("正在初始化游戏...\n");

    // 检查 game 结构体是否已正确分配
    // if (&game == NULL)
    // {
    //     printf("错误:game 结构体未正确初始化\n");
    //     return;
    // }

    printf("清空游戏网格...\n");
    memset(game.grid, 0, sizeof(game.grid));

    printf("初始化游戏参数...\n");
    game.score = 0;
    game.level = 1;
    game.speed = 500;
    game.is_game_over = false;
    game.first_piece = true;
    game.lines_cleared = 0;
    game.combo = 0;

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

    game.current_x = GRID_WIDTH / 2 - 2;
    game.current_y = 0;

    // 使用当前时间作为随机数种子
    srand((unsigned int)time(NULL));

    int shape = rand() % 7;
    int rotations = rand() % 4;

    // printf("选择形状：%d，旋转次数：%d\n", shape, rotations);

    if (game.first_piece)
    {
        memcpy(game.current_piece, SHAPES[shape], sizeof(game.current_piece));
        rotate_piece_times(game.current_piece, rotations);
        game.current_color = lv_color_make(rand() % 256, rand() % 256, rand() % 256);

        shape = rand() % 7;
        rotations = rand() % 4;
        memcpy(game.next_piece, SHAPES[shape], sizeof(game.next_piece));
        rotate_piece_times(game.next_piece, rotations);
        game.next_color = lv_color_make(rand() % 256, rand() % 256, rand() % 256);

        game.first_piece = false;
    }
    else
    {
        memcpy(game.current_piece, game.next_piece, sizeof(game.current_piece));
        game.current_color = game.next_color;

        shape = rand() % 7;
        rotations = rand() % 4;
        memcpy(game.next_piece, SHAPES[shape], sizeof(game.next_piece));
        rotate_piece_times(game.next_piece, rotations);
        game.next_color = lv_color_make(rand() % 256, rand() % 256, rand() % 256);
    }

    if (check_collision())
    {
        game.is_game_over = true;
        // printf("新方块生成时发生碰撞，游戏结束\n");
        return false;
    }

    // 更新下一个方块的显示
    // draw_next_blocK();

    // printf("新方块生成成功\n");
    return true;
}

// 绘制游戏状态
static void draw_game(void)
{
    lv_canvas_fill_bg(game.canvas, lv_color_black(), LV_OPA_COVER);
    lv_draw_rect_dsc_init(&rect_dsc);
    rect_dsc.bg_color = lv_color_hex(0x000000); // 红色
    rect_dsc.border_width = 1;
    rect_dsc.border_color = lv_color_hex(0xffffff); // 红色
    rect_dsc.radius = 0;
    rect_dsc.bg_color = lv_color_make(255, 0, 0); // 红色
    rect_dsc.border_width = 1;
    rect_dsc.border_color = lv_color_make(200, 0, 0); // 深红色边框
    rect_dsc.radius = 2;

    // // 绘制已固定的方块
    // for (int y = 0; y < GRID_HEIGHT; y++)
    // { // 改为 GRID_HEIGHT
    //     for (int x = 0; x < GRID_WIDTH; x++)
    //     { // 改为 GRID_WIDTH

    //         lv_canvas_draw_rect(game.canvas,
    //                             x * BLOCK_SIZE,
    //                             y * BLOCK_SIZE,
    //                             BLOCK_SIZE,
    //                             BLOCK_SIZE,
    //                             &rect_dsc);
    //     }
    // }

    // 绘制已固定的方块
    for (int y = 0; y < GRID_HEIGHT; y++)
    { // 改为 GRID_HEIGHT
        for (int x = 0; x < GRID_WIDTH; x++)
        { // 改为 GRID_WIDTH
            if (game.grid[y][x])
            {
                lv_canvas_draw_rect(game.canvas,
                                    x * BLOCK_SIZE,
                                    y * BLOCK_SIZE,
                                    BLOCK_SIZE,
                                    BLOCK_SIZE,
                                    &rect_dsc);
            }
        }
    }
    // 绘制当前方块
    rect_dsc.bg_color = game.current_color;
    rect_dsc.border_color = lv_color_darken(game.current_color, LV_OPA_50);
    for (int y = 0; y < 4; y++)
    {
        for (int x = 0; x < 4; x++)
        {
            if (game.current_piece[y][x])
            {
                lv_canvas_draw_rect(game.canvas,
                                    (game.current_x + x) * BLOCK_SIZE,
                                    (game.current_y + y) * BLOCK_SIZE,
                                    BLOCK_SIZE,
                                    BLOCK_SIZE,
                                    &rect_dsc);
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
            if (game.current_piece[y][x])
            {
                int new_x = game.current_x + x;
                int new_y = game.current_y + y;                                 // new_x < 0：方块超出左边界
                if (new_x < 0 || new_x >= GRID_WIDTH || new_y >= GRID_HEIGHT || // new_x >= GRID_WIDTH：方块超出右边界
                    (new_y >= 0 && game.grid[new_y][new_x]))
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
            if (game.current_piece[y][x])
            {                                                          // 4x4 数组中的每个位置，检查是否有方块（值为1）
                game.grid[game.current_y + y][game.current_x + x] = 1; // 如果该位置有方块，则将其固定到游戏主网格中
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
            if (!game.grid[y][x])
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
                memcpy(game.grid[yy], game.grid[yy - 1], sizeof(game.grid[0]));
            }
            memset(game.grid[0], 0, sizeof(game.grid[0]));
            y++; // 重新检查当前行
        }
    }
    // 更新总消除行数
    game.lines_cleared += lines_cleared;
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
    int level_multiplier = game.level;
    int combo_bonus = (game.combo > 1) ? game.combo * 50 : 0;
    game.score += (base_score * level_multiplier) + combo_bonus;
    // 更新连击次数
    if (lines_cleared > 0)
    {
        game.combo++;
    }
    else
    {
        game.combo = 0;
    }
    // 检查是否升级
    if (game.lines_cleared / 10 > game.level - 1)
    {
        game.level++;
        game.speed = (int)(game.speed * 0.9); // 加快10%
        lv_timer_set_period(game_timer, game.speed);
    }
}

static bool move_down_and_fix(void)
{
    game.current_y++;
    if (check_collision())
    {
        game.current_y--;
        fix_piece();
        clear_lines();
        //        draw_next_blocK();
        // 检查是否游戏结束
        for (int x = 0; x < GRID_WIDTH; x++)
        {
            if (game.grid[0][x] || game.grid[1][x])
            {
                game.is_game_over = true;
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
    return game.current_piece[0][0] == 1 && game.current_piece[0][1] == 1 &&
           game.current_piece[1][0] == 1 && game.current_piece[1][1] == 1;
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
            if (game.current_piece[y][x])
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
            temp[x][size - 1 - y] = game.current_piece[y][x];
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
                int new_x = game.current_x + x;
                int new_y = game.current_y + y;
                if (new_x < 0 || new_x >= GRID_WIDTH || new_y >= GRID_HEIGHT ||
                    (new_y >= 0 && game.grid[new_y][new_x]))
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
        memcpy(game.current_piece, temp, sizeof(game.current_piece));
    }
}

// 在游戏主循环
static void game_loop(lv_timer_t *timer)
{
    if (game.is_game_over)
    {
        // 游戏结束
        lv_timer_del(game_timer);
        printf("game over\n");
        return;
    }
    if (!move_down_and_fix())
    {
        game.is_game_over = true;
        return;
    }
    draw_game();

    // 更新分数显示
    //    lv_label_set_text_fmt(label_score, "Score: %d", game.score);
    //    lv_label_set_text_fmt(label_level, "Level: %d", game.level);
    //    lv_label_set_text_fmt(label_high_score, "Highest score: %d", game.high_score);
}

// 键盘事件处理
static void keyboard_event_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_timer_t *timer = lv_event_get_user_data(e);

    if (code == LV_EVENT_KEY)
    {
        uint32_t key = lv_event_get_key(e);

        if (!game.is_game_over)
        {
            switch (key)
            {
            case LV_KEY_LEFT:
                game.current_x--;
                if (check_collision())
                    game.current_x++;
                break;
            case LV_KEY_RIGHT:
                game.current_x++;
                if (check_collision())
                    game.current_x--;
                break;
            case LV_KEY_DOWN:
                // 快速下落
                for (int i = 0; i < 3 && !game.is_game_over; i++)
                {
                    if (!move_down_and_fix())
                    {
                        game.is_game_over = true;
                        break;
                    }
                }
                break;
            case LV_KEY_ENTER:
                rotate_piece();
                break;
            case LV_KEY_ESC: // ESC 暂停以及退出操作
                printf("暂停中\n");
                lv_obj_clear_flag(exit_msgbox, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(game_win, LV_OBJ_FLAG_HIDDEN);
                lv_obj_add_flag(info_win, LV_OBJ_FLAG_HIDDEN);
                lv_group_remove_obj(root);
                lv_timer_pause(timer);
                lv_group_focus_obj(btn_exit);
                break;
            }
            if (!game.is_game_over)
                draw_game();
        }
        else
        {
            // // 重置游戏状态
            // init_game();
            // lv_canvas_fill_bg(game.canvas, lv_color_black(), LV_OPA_COVER);
            // lv_obj_add_flag(game_msgbox, LV_OBJ_FLAG_HIDDEN);
            // lv_obj_clear_flag(game_win, LV_OBJ_FLAG_HIDDEN);
            // lv_obj_clear_flag(info_win, LV_OBJ_FLAG_HIDDEN);
            // game_timer = lv_timer_create(game_loop, game.speed, NULL);
            // lv_timer_reset(game_timer);
        }
    }
}

// 重置游戏状态
static void reset_game_state(void)
{
    printf("正在重置游戏状态...\n");
    memset(&game, 0, sizeof(GameState));
    game.level = 1;
    game.speed = 500;
    game.is_game_over = false;
    game.score = 0;
    game.current_x = GRID_WIDTH / 2 - 2;
    game.current_y = 0;
    game.lines_cleared = 0;
    game.combo = 0;
    Pause_Game = false;
}
static void Stop_Game(void)
{
    if (game_timer)
    {
        printf("Deleting game_timer\n");
        lv_timer_del(game_timer);
        game_timer = NULL;
    }
    // 先删除子对象
    if (game.canvas && lv_obj_is_valid(game.canvas))
    {
        printf("Deleting game.canvas\n");
        lv_obj_del(game.canvas);
        game.canvas = NULL;
    }
    if (next_block_canvas && lv_obj_is_valid(next_block_canvas))
    {
        printf("Deleting next_block_canvas\n");
        lv_obj_del(next_block_canvas);
        next_block_canvas = NULL;
    }

    if (next_block__win && lv_obj_is_valid(next_block__win))
    {
        printf("Deleting next_block__win\n");
        lv_obj_del(next_block__win);
        next_block__win = NULL;
    }

    if (game_win && lv_obj_is_valid(game_win))
    {
        printf("Deleting game_win\n");
        lv_obj_del(game_win);
        game_win = NULL;
    }

    if (info_win && lv_obj_is_valid(info_win))
    {
        printf("Deleting info_win\n");
        lv_obj_del(info_win);
        info_win = NULL;
    }
}

void tetris_start_game(lv_obj_t *parent, lv_group_t *group)
{
    // 首先清理旧的资源
    if (game_timer)
    {
        lv_timer_del(game_timer);
        game_timer = NULL;
    }

    create_blocks_canvas(parent);

    init_game();
    if (game_timer)
    {
        lv_timer_del(game_timer);
    }
    game_timer = lv_timer_create(game_loop, game.speed, NULL);
    lv_obj_add_event_cb(parent, keyboard_event_cb, LV_EVENT_KEY, NULL);
    lv_group_add_obj(group, parent);
    lv_timer_reset(game_timer);
}
