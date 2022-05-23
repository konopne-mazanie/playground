import sbt._

lazy val commonSettings = Seq(
  organization := "com.globesy",
  version := "0.1",
  scalaVersion := "2.13.8",
  scalacOptions := List("-encoding", "utf8", "-Xfatal-warnings", "-deprecation", "-unchecked", "-Ymacro-annotations", "-Xasync"),
  libraryDependencies ++= Seq(
    "org.scala-lang" % "scala-library" % "2.13.8",
    "org.scala-lang.modules" %% "scala-async" % "1.0.1",
    "org.scala-lang" % "scala-reflect" % scalaVersion.value % Provided,
    "com.typesafe.scala-logging" %% "scala-logging" % "3.9.4",
    "ch.qos.logback" % "logback-classic" % "1.2.11",
    "com.typesafe.akka" %% "akka-actor" % "2.6.19",
    "com.typesafe.akka" %% "akka-stream" % "2.6.19",
    "com.typesafe.akka" %% "akka-http" % "10.2.9",
    "io.circe" %% "circe-core" % "0.14.1",
    "io.circe" %% "circe-generic" % "0.14.1",
    "io.circe" %% "circe-parser" % "0.14.1"
  )
)

lazy val application = (project in file("app"))
  .settings(
    commonSettings,
    name := "application",
  )

lazy val root = (project in file("."))
  .settings(
    name := "globesy",
    Compile / mainClass := Some("com.globesy.Runner"),
    commonSettings
  )
  .dependsOn(application)
  .aggregate(
    application,
  )
