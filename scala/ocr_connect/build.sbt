name := "ocr_connect"

version := "0.1"

scalaVersion := "2.13.6"

libraryDependencies += "com.typesafe.akka" %% "akka-actor-typed" % "2.6.15"
libraryDependencies += "ch.qos.logback" % "logback-classic" % "1.2.3"
libraryDependencies += "com.typesafe.akka" %% "akka-stream" % "2.6.15"
libraryDependencies += "com.lightbend.akka" %% "akka-stream-alpakka-unix-domain-socket" % "3.0.1"
// "com.typesafe.akka" %% "akka-actor-testkit-typed" % akkaVersion % Test,
// "org.scalatest" %% "scalatest" % "3.1.0" % Test
