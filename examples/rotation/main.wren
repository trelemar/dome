import "graphics" for Canvas, ImageData, Color
import "plugin" for Plugin
import "flap" for Grid

Plugin.load("transform")
import "transform" for Transform

class Main {
  construct new() {}

  init() {
    _sheet = Transform.loadFromFile("sheet.png")
    _grid = Grid.new(32, 32, 320, 32)
    _t = 0
  }

  update() {}

  draw(alpha) {
    Canvas.cls(Color.blue)
    //Transform.draw(_food, 0, 0)

    for (slice in 0..9) {
      _sheet.rdraw(Canvas.width/2, Canvas.height/2 - (slice * 2.5), {
        "angle": _t,
        "srcX": _grid.getX(slice),
        "srcY": _grid.getY(slice),
        "srcW": _grid.frameWidth,
        "srcH": _grid.frameHeight,
        "scaleX": 1.5,
        "scaleY": 1
      })
    }

    /*
    _sheet.rdraw(Canvas.width/2, Canvas.height/2, {
      "angle": _t,
      "srcX": 0,
      "srcY": 0,
      "srcW": 32,
      "srcH": 32,
      "scaleX": 3,
      "scaleY": 1
      })
    */
    _t = _t + 2
    Canvas.print(_sheet.width, 2, 2, Color.white)
  }
}

var Game = Main.new()
