import "graphics" for Canvas, Color, ImageData, Point, Font
import "io" for FileSystem
import "dome" for Platform, Window
import "flap" for Grid, Animation, SpriteSheet
import "random" for Random
var OurRand = Random.new(System.clock)
var Sheet = SpriteSheet.new("./basictiles.png", 16, 16)
class Main {
  construct new() {}
  init() {
    Canvas.resize(320, 240)
    __frametimes = []
    __t = 0
  }
  update() {
    if (__frametimes.count > 2 && __frametimes.count % 10 == 0) {
      var tot = 0
      for (i in __frametimes.count - 11...__frametimes.count) {
        tot = tot + __frametimes[i]
      }
      __frametimes.clear()
      System.print("%(__t) %(tot/10)")
    }
    if (Window.fps <= 55) {
      Fiber.abort("Took %(__t) sprites to drop 5 frame")
    }
  }
  draw(alpha) {
    __t = __t + 1
    var start = System.clock
    //Canvas.cls(Color.black)
    Canvas.print("w: %(Canvas.width)", 2, 2, Color.white)
    for (i in 0...__t) {
      var idx = OurRand.int(80)
      //var c = Color.rgb(OurRand.int(255), OurRand.int(255), OurRand.int(255))
      //Canvas.rectfill(OurRand.int(320), OurRand.int(240), OurRand.int(320), OurRand.int(240), c)
      //Sheet.image.drawArea(Sheet.grid.getX(idx), Sheet.grid.getY(idx), 16, 16, OurRand.int(320/16) * 16, OurRand.int(240/16)*16)
      //Sheet.image.drawArea(Sheet.grid.getX(idx), Sheet.grid.getY(idx), 16, 16, OurRand.int(320 - 16), OurRand.int(240 - 16))
      Sheet.image.transform({
        "srcX": Sheet.grid.getX(idx),
        "srcY": Sheet.grid.getY(idx), 
        "srcW": 16, 
        "srcH": 16,
        "scaleX": 1,
        "scaleY": 1,
        "angle": 90
      }).draw(OurRand.int(320 - 16), OurRand.int(240 - 16))
    }
    __frametimes.add(System.clock - start)
  }
}

var Game = Main.new()