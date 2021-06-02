object MyFullClassTest {
    def main(args: Array[String]): Unit = {
        var myFullClass = new MyFullClass(1)
        myFullClass.publicFn()

        val myFullClass2 = new MyFullClass(input=2)

        val myFullClassWTrait = new MyFullClass(1) with MyTrait2
        myFullClassWTrait.willOverride()
        myFullClassWTrait.implemented()
        myFullClassWTrait.implemented2()
    }
}
