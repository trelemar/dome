import "dome" for Window
import "graphics" for Canvas, Color, ImageData
class Main {
  construct new() {}
  init() {
    _t = 0
    _spr = ImageData.loadFromFile("Food.png")
  }
  update() {}
  draw(dt) {
    Canvas.cls()
    Canvas.print("DOME Installed Successfully.", 10, 10, Color.white)
    //Graphics.cls()
    //Graphics.line(2, 2, 0, _t, Color.white, 5)
    //_spr.draw(0, 0)
    //Graphics.line(0, _t, 20, _t, Color.white, 5)
    //_spr.drawDirect(0,0,0)
    _spr.draw(0,0)
    _t = _t + 1
    System.print(Window.fps)
  }
}

var Game = Main.new()
