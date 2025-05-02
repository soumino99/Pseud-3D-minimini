#include <iostream>
#include <cmath>
#include <conio.h>
#include <windows.h>

const int まっぷよこ = 16;
const int まっぷたて = 16;
const float しせんはんけい = 3.14159f / 4.0f;
const float みえるきょり = 16.0f;
const int がめんよこ = 120;
const int がめんたて = 40;
const float あるくはやさ = 0.5f;
const float まわるはやさ = 0.1f;

std::string まっぷ =
    "################"
    "#..............#"
    "#..............#"
    "#...##.........#"
    "#..............#"
    "#..............#"
    "#......###.....#"
    "#..............#"
    "#..............#"
    "#..............#"
    "#.......####...#"
    "#..............#"
    "#..............#"
    "#..............#"
    "#..............#"
    "################";

// がめんのサイズをせっていする
void がめんをせっていする(HANDLE こんそーる, int よこ, int たて)
{
    COORD さいず = {(SHORT)よこ, (SHORT)たて};
    SetConsoleScreenBufferSize(こんそーる, さいず);
    SMALL_RECT ばしょ = {0, 0, (SHORT)(よこ - 1), (SHORT)(たて - 1)};
    SetConsoleWindowInfo(こんそーる, TRUE, &ばしょ);
}

// そこがかべか たしかめる
bool かべかな(float x, float y)
{
    int ix = (int)x;
    int iy = (int)y;
    if (ix < 0 || ix >= まっぷよこ || iy < 0 || iy >= まっぷたて)
        return true;
    return まっぷ[iy * まっぷよこ + ix] == '#';
}

int main()
{
    HANDLE こんそーる = GetStdHandle(STD_OUTPUT_HANDLE);
    がめんをせっていする(こんそーる, がめんよこ, がめんたて);

    float じぶんx = 14.7f, じぶんy = 5.09f, じぶんのかお = 0.0f;
    char *がめん = new char[がめんよこ * がめんたて + 1];
    がめん[がめんよこ * がめんたて] = '\0';

    while (true)
    {
        // きーぼーどをみる
        if (_kbhit())
        {
            char きー = _getch();
            float dx = sinf(じぶんのかお) * あるくはやさ;
            float dy = cosf(じぶんのかお) * あるくはやさ;

            if (きー == 'a')
                じぶんのかお -= まわるはやさ;
            if (きー == 'd')
                じぶんのかお += まわるはやさ;
            if (きー == 'w')
            {
                if (!かべかな(じぶんx + dx, じぶんy + dy))
                {
                    じぶんx += dx;
                    じぶんy += dy;
                }
            }
            if (きー == 's')
            {
                if (!かべかな(じぶんx - dx, じぶんy - dy))
                {
                    じぶんx -= dx;
                    じぶんy -= dy;
                }
            }
        }

        // えをかく
        for (int x = 0; x < がめんよこ; ++x)
        {
            float れいかく = (じぶんのかお - しせんはんけい / 2.0f) + ((float)x / がめんよこ) * しせんはんけい;
            float みるx = sinf(れいかく);
            float みるy = cosf(れいかく);
            float きょり = 0.0f;

            while (きょり < みえるきょり && !かべかな(じぶんx + みるx * きょり, じぶんy + みるy * きょり))
            {
                きょり += 0.1f;
            }

            int てんじょう = (int)((がめんたて / 2.0f) - がめんたて / きょり);
            int ゆか = がめんたて - てんじょう;

            for (int y = 0; y < がめんたて; ++y)
            {
                char moji = (y < てんじょう) ? ' ' : (y <= ゆか ? '#' : '.');
                がめん[y * がめんよこ + x] = moji;
            }
        }

        // ひょうじする
        SetConsoleCursorPosition(こんそーる, {0, 0});
        std::cout.write(がめん, がめんよこ * がめんたて);
        std::cout << "\nX=" << じぶんx << " Y=" << じぶんy << " A=" << じぶんのかお;
    }

    delete[] がめん;
    return 0;
}
