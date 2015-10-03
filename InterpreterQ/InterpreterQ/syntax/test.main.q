:SYSMEMALLOC(16); /*Allocate 256 bytes*/
/*RESERVED: bytes 0 - 128 . Heap*/
/*RESERVED: bytes 129 - 256. Stack */

:include("../anotherFile.q");
:include("../stack.q");

$subroutine printString {
	alias txtA : #000190 - #000197 = 'A','d', 'd','r','e','s','s',':', '\0';
	alias txtB : #000198 - #000204 = 'V', 'a', 'l', 'u', 'e', ':', '\0';

	:printS(txtA);
	:printA(cStr);

	:printS(txtB);
	:printV(cStr);
}

$subroutine printNumber {
	/*OBSERVE that memory is never freed it only get overwriten.*/
	alias txt : #000190 - #000206 = 'H', 'i', 'g', 'h', 'e', 's', 't', ' ', 'n', 'u', 'm', 'b', 'e', 'r', ':', '\0'; 

	:printS(txt);
	:printV(#000017);
}

$subroutine printNumbers {
	alias txt : #000135 - #000149 = 'v', 'a', 'l', 'u', 'e', ' ', 'o', 'f', ' ', 'i', ':', ' ';
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

$subroutine getMax {
	alias max : #000136 = 0; /*4 bytes*/
	alias i : #000134 = 0;

	while (i != 10) {
		if (max < (numbers + i)) {
			// #000035 = #000008 + i; //TODO! förtydliga att numbers är första minnesplatsen!
			max = (numbers + i);
		}
		++i;
	}

	#000017 = max;
}

alias cStr : #000001 - #000006 = 'h','e','l','l','o','/0';

test$printString;

alias numbers : #0000050 - #000089;
numbers = 1, 9, 3, 4, 7, 2, 4, 8, 5, 6 ;

$getMax();
test$printNumber;

test$printNumbers;

anotherFile$add;
test$printNumber;

alias p : #000039 - #000040 = 'p','\0';
anotherFile$append;
test$printString;

:system("pause"); /*Same functionalite as C.*/