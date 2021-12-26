import "graphics" for Canvas, Color
import "input" for Keyboard
import "dome" for Window
import "math" for Vector

class Main {
  construct new() {}
  init() {
  	_scale = 2
  	_box = Vector.new(320/2, 240/2, 320, 240)
  }
  update() {
  	if (Keyboard["="].justPressed) {
  		_scale = _scale + 1
  	} else if (Keyboard["-"].justPressed) {
  		_scale = (_scale - 1).max(1)
  	}
  }
  draw(alpha) {
  	Canvas.resize((Window.width / _scale).floor, (Window.height / _scale).floor)
  	Canvas.cls(Color.lightgray)
  	Canvas.print("w: %(Canvas.width)\nh: %(Canvas.height)\nscale: %(_scale)", 0, 0, Color.black)
  	Canvas.clip(_box.x, _box.y, _box.z, _box.w)
  	Canvas.rectfill(_box.x, _box.y, _box.z, _box.w, Color.black)
  	Canvas.rect(_box.x, _box.y, _box.z, _box.w, Color.white)
  	Canvas.print("Hello World", _box.x, _box.y, Color.red)
  	Canvas.clip()
  }
}

var Game = Main.new()