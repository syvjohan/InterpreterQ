:SYSMEMALLOC("000000", 256); /*Allocate 256 bytes*/
/*RESERVED: bytes 0 - 128 memmory for alias names.*/
/*RESERVED: bytes 129 - 189 loop.*/
/*RESERVED: bytes 190 - 256 text inside print.*/

:include("../anotherFile.q");

.function printString(cStr) {
/*:print can print value (%v) or address (%a).*/
	alias txtA : #000190 - #000197 = 'A','d', 'd','r','e','s','s',':', '\0';
	alias txtB : #000198 - #000204 = 'V', 'a', 'l', 'u', 'e', ':', '\0';
	:print(txtA, "%a\n", cStr);
	:print(txtB, "%v\n", cStr);
}

.function printNumber(#000017) {
	/*OBSERVE that memory is never freed it only get overwriten.*/
	alias txt : #000190 - #000206 = 'H', 'i', 'g', 'h', 'e', 's', 't', ' ', 'n', 'u', 'm', 'b', 'e', 'r', ':', 

'\0';
	:print(txt, "%v\n", #000017);
}

.function printNumbers() {
	alias LOOP : #000129 - #000133 = 'L', 'O', 'O', 'P', '\n';
	alias i : #000134 = 10;
	:do.LOOP {
		if ( i == 15) {
			i = i + 1;
			goto.LOOP;
		}
		:print("value of i is: %v\n", i);
		i++;

	} :while.LOOP (i < 20);
}

.function getMax(numbers) {
	alias max : #000136 = 0;
	alias i : #000134 = 0;
	alias repeat : #000129 - #000135 = 'r', 'e', 'p', 'e', 'a', 't', '\0';
	:do.repeat {
		if (max < (numbers + i)) {
			// #000035 = #000008 + i; //TODO! förtydliga att numbers är första minnesplatsen!
			max = (numbers + i);
		}
		++i;
	} :while.repeat (i != 10);

	return max;
}

#000001 - #000006 = 'h','e','l','l','o','/0';
alias cStr : #000001 - #000006;

this.printString(cStr);

alias numbers : #0000050 - #000089;
numbers = 1, 9, 3, 4, 7, 2, 4, 8, 5, 6 ;

#000017 = .getMax(numbers);
this.printNumber(#000017);

this.printNumbers(numbers);

#000037 = anotherFile.add(#000050 - #000053, #000086 - #000089);
this.printNumber(#000037);

alias p : #000039 - #000040 = 'p','\0';
#000038 = anotherFile.append(#000001 - #000006, p);
this.printString(#000038);


:system("pause"); /*Same functionalite as C.*/