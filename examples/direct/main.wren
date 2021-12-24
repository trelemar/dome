import "graphics" for Canvas, Color, Graphics
class Main {
  construct new() {}
  init() {
    _t = 0
  }
  update() {}
  draw(dt) {
    Canvas.cls()
    Canvas.print("DOME Installed Successfully.", 10, 10, Color.white)
    //Graphics.line(2, 2, 0, _t, Color.white, 5)
    Graphics.line(0, _t, 20, _t, Color.white, 5)
    _t = _t + 1
  }
}

var Game = Main.new()
