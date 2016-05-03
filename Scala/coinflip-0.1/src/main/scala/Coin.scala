import scala.util.Random

class Coin {
    var coinOption : String = ""

    def getCoinOption : String = {
      val r = new Random
      coinOption = if (r.nextInt(2) == 0) "Heads" else "Tails"

      print(s"Coin got: $coinOption\n")
      coinOption
    }
}
