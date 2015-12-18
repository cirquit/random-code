import java.io.PrintStream

trait Account extends Logger {

  private var pbalance = 0
  log("Account created")

  def deposit(amount : Int) : Unit = {
    pbalance += amount
    log("Deposit of " + amount)
  }

  def balance() : BigInt = {
    log("Balance: " + pbalance)
    pbalance
  }

}

trait Logger {
  def log(msg : String) : Unit
}

trait ConsoleLogger extends Logger {
  def log(msg : String) : Unit = println("Log: " + msg) 
}

trait TimestampLogger extends Logger{

  val datef = new java.text.SimpleDateFormat("dd-MM-yy | kk:mm:ss")
  val date  = datef.format(new java.util.Date())

  abstract override def log(msg : String) : Unit = super.log(date + " @ " + msg)
}

trait ShortLogger extends Logger {
  val maxLength : Int
  abstract override def log(msg : String) : Unit = msg match {
    case _ if msg.length > maxLength => super.log(msg.take(maxLength) + "...")
    case _                           => super.log(msg)
  }
  
}

trait FileLogger extends Logger {
  val filename : String
  lazy val out = new PrintStream(filename)
  def log(msg : String) : Unit = { out.println(msg + "\n"); out.flush }
}




object MyLogger extends App {
  //var acc = new { val filename = "acct.log" } with Account
  var acc = new {val filename = "hallo.log"} with Account with FileLogger
  //var acc = new Account
  acc.deposit(10)
  acc.balance
}

// object MyLogger {
//   def main(args: Array[String]) : Unit = {
//     var acc = new Account()
//     acc.deposit(10)
//   }
// }


// trait ShortLogger extends Logger{
  // val maxLength = 50
  // abstract override def log(msg : String){
    // super.log(msg.length match{
      // case n if n > maxLength => msg.take(maxLength - 3) + "..."
      // case _                  => msg
    // })
  // }
// }