package javapkg;


import frege.prelude.PreludeBase.TList;
import fregepkg.FregeProducer;

public class Consumer {

	public static void main(String[] args) {

		FregeProducer.testio.result().forced();
		
		TList jevens = FregeProducer.evens.<TList>forced();
		int var1 = FregeProducer.getElem(1, jevens);
		System.out.println(var1);
	}

}
