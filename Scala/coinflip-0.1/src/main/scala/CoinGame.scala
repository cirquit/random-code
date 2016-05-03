import scala.util.Random

/**
  * Created by rewrite on 04/02/16.
  */

// trait CoinValue

// case class Heads implements CoinValue
// case class Tails


class CoinGame {

    var players : List[Player] = Nil
    val theCoin : Coin         = new Coin

    def startGame : Unit = {
        val p1 = new Player("Hugo")
        val p2 = new Player("Boss")
        players = p1 :: p2 :: players

        val r = new Random
        if (r.nextInt(2) == 0) {
              p1.getRandCoinOption
              p2.setCoinOption(p1.coinOption)
        } else {
            p2.getRandCoinOption
            p1.setCoinOption(p2.coinOption)
        }

        val coin = new Coin
        val res = coin.getCoinOption

        p1.didPlayerWin(res)
        p2.didPlayerWin(res)

        print("Again? Y/N\n")
        readLine match {
          case "Y" => this.startGame
          case _  => ()
        }

    }
}
