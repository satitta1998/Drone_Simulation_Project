#include "WorldGrid.h"
#include "EmptyTile.h"
#include "ExitTile.h"
#include "WallTile.h"
#include <assert.h>

//.#..#
//....#
//#.###
//E...#
//#####

void checkBeginZeroIdxGridCell(const jb::WorldGrid & w)
{
    jb::WorldGrid::const_iterator itr = w.begin(jb::Position{ 0,0 });
    assert(*itr == &jb::EmptyTile::getInstance());
}

void checkBeginForMiddleCell(const jb::WorldGrid& w)
{
    {
        jb::WorldGrid::const_iterator itr = w.begin(jb::Position{ 1,1 });
        assert(*itr == &jb::EmptyTile::getInstance());
    }
    {
        jb::WorldGrid::const_iterator itr = w.begin(jb::Position{ 0,3});
        assert(*itr == &jb::ExitTile::getInstance());
    }
    {
        jb::WorldGrid::const_iterator itr = w.begin(jb::Position{ 3,2 });
        assert(*itr == &jb::WallTile::getInstance());
    }
}

void checkOutOfBounds(const jb::WorldGrid & w)
{
    jb::WorldGrid::const_iterator itr = w.begin(jb::Position{ -1,1 });
    assert(*itr == &jb::WallTile::getInstance());
}

void checkEndLine(const jb::WorldGrid& w)
{
    jb::WorldGrid::const_iterator itr = w.begin(jb::Position{ 4,0 });
    jb::WorldGrid::const_iterator end = w.end(jb::Position{ 0,1 });
    ++itr;
    assert(itr == end);
}

void checkGoToEnd(const jb::WorldGrid& w)
{
    jb::WorldGrid::const_iterator itr = w.begin(jb::Position{ 0,0 });
    jb::WorldGrid::const_iterator end = w.end(jb::Position{ 4,2 });
    while (itr != end)
    {
        ++itr;
    }
    assert(itr == end);
}

//
//int main()
//{
//    std::ifstream inputFile("world_grid.txt");
//    const jb::WorldGrid theWorld{ inputFile };
//    inputFile.close();
//
//    checkBeginZeroIdxGridCell(theWorld);
//    checkBeginForMiddleCell(theWorld);
//    checkOutOfBounds(theWorld);
//    checkEndLine(theWorld);
//    checkGoToEnd(theWorld);
//}