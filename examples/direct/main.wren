import "dome" for Window
import "graphics" for Canvas, Color, ImageData, Graphics
import "input" for Keyboard
class Main {
  construct new() {}
  init() {
    Canvas.resize(800, 600)
    _t = 0
    _moat = ImageData.loadFromFile("moat.png")
    _food = ImageData.loadFromFile("Food.png")
    _sample = ImageData.loadFromFile("sample.png")
    _start = System.clock.toString
    _smooth = false
    _zoom = 1
  }
  update() {
    if (Keyboard["z"].justPressed) {
      _smooth = !_smooth
    }
    if (Keyboard["Up"].down) {
      _zoom = _zoom + 0.1
    }
    if (Keyboard["Down"].down) {
      _zoom = _zoom - 0.1
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
    _sample.drawDirect(Canvas.width / 2 - (_sample.width / 2), (Canvas.height / 2) - (_sample.height / 2), _t, 2.5 * _zoom, 0.5 * _zoom, _smooth)
    
    //_food.drawDirect(0, 0, 45, 0.5, 2, _smooth)
    _food.drawDirect(0, 0, _t, -1, -1, _smooth)
    //_food.drawDirect(0, _food.height, 0, 1, -1, _smooth)
    //_food.drawDirect(_food.width, _food.height, 0, -1, -1, _smooth)

    Canvas.print("bg:\nScale:\n\tx:%(scalex)\n\ty:%(scaley)", 0, 0, Color.white)
    Canvas.print("Anti-aliasing %(_smooth)", 0, Canvas.height - 8, Color.white)
    _t = _t + 1
  }
}

var Game = Main.new()
