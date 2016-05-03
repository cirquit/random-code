/**
  * Created by rewrite on 04/02/16.
  */

import scala.util.Random

class Player(name : String) {

    var coinOption : String = ""

    def setCoinOption(opponentFlip : String) : Unit = {
        coinOption = if (opponentFlip.equals("Tails")) "Heads" else "Tails"
    }

    def getRandCoinOption : String = {
        val r = new Random
        coinOption = if (r.nextInt(2) == 0) "Heads" else "Tails"
        coinOption
    }

    def didPlayerWin(winningFlip : String) : Unit = {
        val maybe = if (winningFlip == coinOption) "indeed" else "not"
        print(s"$name did have $coinOption. He did $maybe win.\n")
    }
}
