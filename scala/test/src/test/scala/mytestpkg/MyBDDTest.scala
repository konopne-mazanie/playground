package mytestpkg

import org.scalatest.funspec.AnyFunSpec

import MyPackage._

class MyBDDTest extends AnyFunSpec{
    describe("MyFullClass::returnPublicMutableInt") {
        it("should return 1") {
            assert(ForTestingClass.forTestingFn(0) == 1)
        }
    }

}
