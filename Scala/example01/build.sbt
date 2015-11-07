name := "example01"

version := "0.1.0-SNAPSHOT"

scalaVersion := "2.11.7"

libraryDependencies ++= Seq(
  "org.scalatest" % "scalatest_2.11" % "2.2.4" % "test", 
  "org.scalacheck" %% "scalacheck" % "1.12.5" % "test",
  "org.scalamock" %% "scalamock-scalatest-support" % "3.2" % "test"
)

scalacOptions in Test ++= Seq("-Yrangepos")

