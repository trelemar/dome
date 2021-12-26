import "dome" for Window
import "graphics" for Canvas, Color, ImageData, Graphics
import "input" for Keyboard
class Main {
  construct new() {}
  init() {
    Canvas.resize(400, 300)
    _t = 0
    _moat = ImageData.loadFromFile("moat.png")
    _food = ImageData.loadFromFile("Food.png")
    _start = System.clock.toString
    _smooth = false
  }
  update() {
    if (Keyboard["z"].justPressed) {
      _smooth = !_smooth
    }
  }
  draw(dt) {
    Canvas.cls()
    Canvas.rectfill(0, 0, Canvas.width, Canvas.height, Color.none)
    /*
    for (i in 0...(_t/30).floor) {
      _spr.drawDirect(i * 2,0,_t)
    }
    */
    var scalex = ((_t/3.14/8).sin) + 1.5
    var scaley = -((_t/3.14/8).sin) + 1.5
    _moat.drawDirect(Canvas.width / 2 - (_moat.width / 2), (Canvas.height / 2) - (_moat.height / 2), -_t, scalex, scaley, _smooth)
    _food.drawDirect(64, 64, 0, (_t/30).sin, 1, _smooth)
    Canvas.print("bg:\nScale:\n\tx:%(scalex)\n\ty:%(scaley)", 0, 0, Color.white)
    Canvas.print("Anti-aliasing %(_smooth)", 0, Canvas.height - 8, Color.white)
    _t = _t + 1
  }
}

var Game = Main.new()
