trait MyTrait {
    def willOverride() : Unit
    def implemented() : Unit = {
        println("implemented")
    }
}
