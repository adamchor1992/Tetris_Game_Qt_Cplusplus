#include "tetris.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Tetris tetris;

    return QApplication::exec();
}
