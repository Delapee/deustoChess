
#include "piece.h"
#include <blah.h>
#include "chess.h"
namespace chessSprite
{
   bool Piece::hover = false;

    Piece::Piece(const String& texturePath, std::string pos)
    {
        this->texture = Texture::create(texturePath);
        this->grabbed = false;
        this->pos = pos;
    }

    void Piece::draw(Batch* batch, char c)
    {
        Vec2 pos;

        if (true) {
            pos.x = (this->pos.at(0) - 'a') * 115.5 + 465;
            pos.y = ('8' - this->pos.at(1)) * 115 + 100;
        }
        else{
            pos.x = ('h' - this->pos.at(0)) * 115.5 + 465;
            pos.y = (this->pos.at(1) - '1') * 115 + 100;
        }

        batch->tex(this->texture, pos);
    }

    std::string Piece::getPos() {
        return this->pos;
    }

    void Piece::setPos(std::string pos) {
        this->pos = pos;
    }

    bool Piece::getHover()
    {
        return this->hover;
    }

    void Piece::setHover(bool bo) {
        hover = bo;
    }

    bool Piece::isGrabbed() {
        return this->grabbed;
    }

    void Piece::setGrabbed(bool grabbed) {
        this->grabbed = grabbed;
    }

    void Piece::drawMouse(Batch* batch) {

        int x = Input::mouse().x - 52.75;
        int y = Input::mouse().y - 52.75;
        Vec2 a = Vec2(x, y);

        batch->tex(this->texture, a);
    }
}