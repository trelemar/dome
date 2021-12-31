import "graphics" for Canvas, ImageData, Color
import "plugin" for Plugin

Plugin.load("transform")
import "transform" for Transform

class Main {
  construct new() {}

  init() {
    _food = ImageData.loadFromFile("Food.png")
    Transform.draw(_food, 0, 0)
  }

  update() {}

  draw(alpha) {
    Canvas.cls(Color.blue)
    //Transform.draw(_food, 0, 0)
  }
}

var Game = Main.new()
