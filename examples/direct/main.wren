import "dome" for Window
import "graphics" for Canvas, Color, ImageData, Graphics
import "input" for Keyboard
import "math" for Math, Vector

class Main {
  construct new() {}
  init() {
    Canvas.resize(360*2, 120*3)
    Window.resize(360*2, 120*3)
    _t = 0
    _moat = ImageData.loadFromFile("moat.png")
    _food = ImageData.loadFromFile("Food.png")
    _sample = ImageData.loadFromFile("new.png")
    _map = ImageData.loadFromFile("map.png")
    _water = ImageData.loadFromFile("water.png")
    _start = System.clock.toString
    _smooth = false
    _zoom = 1
    _step = 0
    _map = _water
    _exps = ["SDL_gfx", "3 shears", "rotation matrix"]
    _times = []
    _total = 0
  }
  update() {
    if (Keyboard["z"].justPressed) {
      _step = _step + 5
    }
    if (Keyboard["x"].justPressed) {
      _step = _step - 5
    }
    _total = 0
    for (pair in _times) {
      _total = _total + pair
    }

  }
  draw(alpha) {
  	Canvas.cls(Color.white)
  	var roto = _map.drawDirect(Math.lerp(0, Canvas.width, 0.25)* Canvas.width - _map.width/2, Canvas.height/2 - _map.height/2, _t, 1, 1, false)
    var shear = _map.drawShear(Math.lerp(0, Canvas.width, 0.50)* Canvas.width - _map.width/2, Canvas.height/2 - _map.height/2, _t, 1, 1, false)
    _map.drawSample(Math.lerp(0, Canvas.width, 0.75)* Canvas.width - _map.width/2, Canvas.height/2 - _map.height/2, _t, 1, 1, false)
    Canvas.print(_exps[0], Math.lerp(0, Canvas.width, 0.25)* Canvas.width - Canvas.getPrintArea(_exps[0]).x/2, 10, Color.black)
    Canvas.print(_exps[1], Math.lerp(0, Canvas.width, 0.50)* Canvas.width - Canvas.getPrintArea(_exps[1]).x/2, 10, Color.black)
    Canvas.print(_exps[2], Math.lerp(0, Canvas.width, 0.75)* Canvas.width - Canvas.getPrintArea(_exps[2]).x/2, 10, Color.black)
    //_food.drawDirect((Canvas.width/6) * 2, 64, _step, 1, 1, false)
  	_t = _t + 1
    _times.add(shear/roto)
  	Canvas.print((_step%360).toString, 0, 0, Color.white)
    Canvas.print(_total/_times.count,32, 32, Color.black)
  }
}

var Game = Main.new()