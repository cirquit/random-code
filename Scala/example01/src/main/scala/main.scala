object Hi {

  def sort(xs : Seq[Int]) : Seq[Int] = xs match {
    case Seq()                => Seq()
    case Seq(head, tail @ _*) =>
      val lesser  = for (n <- tail if n <  head) yield n
      val greater = for (n <- tail if n >= head) yield n
      sort(lesser) ++ (head +: sort(greater))
  }

  def findOdd(xs : Seq[Int]) : Option[Int] = xs match {
    case Seq()          => None
    case Seq(head , _*) =>
      def go(tup : (Int,Int), xs : Seq[Int]) : Int = (tup, xs) match {
        case ((  _, num), Seq()                            => num
        case ((acc, num), Seq(x, xs @ _*)) if num == x     => go((acc+1, num), xs)
        case ((acc, num), Seq(x, xs @ _*)) if acc % 2 == 1 => num
        case ((  _, num), Seq(x, xs @ _*))                 => go((    0,   x), xs)
      }
      Some( go((0, head), xs.sorted) )
  }

  def main(args: Array[String]) = {
    // var seq = Seq(1,5,7,9,1,4,5,9)
    // println (s"Before sorting: ${seq} dasd blub")
    // println (s"After sorting: ${sort(seq)}")
    val list = Seq()
    findOdd(list) match {
      case Some(res) => println (s"Result found = ${res}!")
      case None      => println (s"Result not found - list must be empty!")
    }
    
    
    // println (s"foldRight    => ${list.foldRight(list.head)(_ ^ _)}")

  }
}