sealed trait MyEnum
case object Val1 extends MyEnum
case object Val2 extends MyEnum

class MyFullClass(input : Int) extends MyAbstractClass(input) with MyTrait {
    private val privateInt : Int = 20
    var publicMutableInt : Int = 0
    println("body ctor")

    val myEnum : MyEnum = Val1

    def this(input : Int, input2: String) = {
        this(input)
        val publicMutableInt = input
        this.publicMutableInt = input + 1
        println(publicMutableInt)
        println(this.publicMutableInt)
    }

    private def privateFn(): Unit = {
        println(privateInt)
    }

    def publicFn(): Unit = {
        privateFn()
    }

    override def willOverride(): Unit = {
        println("was overridden")
    }
}
