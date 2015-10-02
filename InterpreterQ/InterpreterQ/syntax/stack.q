
alias size;

alias currentPtr;

alias begin;

alias end;



$function setStackSize(start, end) {
	
	size : start - end;

	this.begin = start;

	this.end = end;

}



$function getPtr() {

	return currentPtr;

}



$function getBeginPtr() {

	return this.begin;

}

$function getEndPtr() {

	return this.endPtr;

}



$function setPtr(address) {

	this.currentPtr = address;

}



$function getStackSize() {

	return size;

}