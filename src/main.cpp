#include "Engine.h"
#include "ObjScene.h"

int main(int argc, char const *argv[])
{
    auto game = Geno3D::Engine(500, 500, "Geno3D");
    game.scene = new Geno3D::ObjScene(argv[1], 200, -600);
    game.run();
    return 0;
}