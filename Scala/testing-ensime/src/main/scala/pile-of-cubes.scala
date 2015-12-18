object Pile_of_cubes extends App {

  def findNB(n : Long) : Long = {
    def go(acc : Long, cur : Long) : Long = {
      val nacc = acc - cur*cur*cur
      acc match {
        case 0              => cur
        case _ if nacc < 0  => -1
        case _              => go (nacc, cur+1)
      }
    }
    go (n, 0)
  }
  assert()
  assert(findNB(4183059834009L  ) == 2022)
  assert(findNB(24723578342962L ) ==   -1)
  assert(findNB(135440716410000L) == 4824)
  assert(findNB(40539911473216L ) == 3568)
}
