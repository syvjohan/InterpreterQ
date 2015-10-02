:SYSMEMALLOC(16); /*Allocate 256 bytes*/
/*RESERVED: bytes 0 - 128 .*/
/*RESERVED: bytes 129 - 256. Stack */

:include("../anotherFile.q");
:include("../stack.q");

$subroutine printString(cStr) {
	alias txtA : #000190 - #000197 = 'A','d', 'd','r','e','s','s',':', '\0';
	alias txtB : #000198 - #000204 = 'V', 'a', 'l', 'u', 'e', ':', '\0';

	:printS(txtA);
	:printA(cStr);

	:printS(txtB);
	:printV(cStr);
}

$subroutine printNumber(#000017) {
	/*OBSERVE that memory is never freed it only get overwriten.*/
	alias txt : #000190 - #000206 = 'H', 'i', 'g', 'h', 'e', 's', 't', ' ', 'n', 'u', 'm', 'b', 'e', 'r', ':', '\0';

	:printS(txt);
	:printV(#000017);
}

$subroutine printNumbers() {
	alias txt : #000135 - #000148 = 'v', 'a', 'l', 'u', 'e', ' ', 'o', 'f', 'i', 'i', 's';
	alias i : #000134 = 10;

	:LOOP
	:while(i < 20) {

		if (i == 15) {
			i = i + 1;
			:goto.LOOP;
		}
		:printS(txt);
		:printV(i);
		i++;
	}
}

$subroutine getMax(numbers) {
	alias max : #000136 = 0;
	alias i : #000134 = 0;

	while (i != 10) {
		if (max < (numbers + i)) {
			// #000035 = #000008 + i; //TODO! förtydliga att numbers är första minnesplatsen!
			max = (numbers + i);
		}
		++i;
	}

	return max;
}

#000001 - #000006 = 'h','e','l','l','o','/0';
alias cStr : #000001 - #000006;

test$printString(cStr);

alias numbers : #0000050 - #000089;
numbers = 1, 9, 3, 4, 7, 2, 4, 8, 5, 6 ;

#000017 = $getMax(numbers);
test$printNumber(#000017);

test$printNumbers(numbers);

#000037 = anotherFile$add(#000050 - #000053, #000086 - #000089);
test$printNumber(#000037);

alias p : #000039 - #000040 = 'p','\0';
#000038 = anotherFile$append(#000001 - #000006, p);
test$printString(#000038);


:system("pause"); /*Same functionalite as C.*/