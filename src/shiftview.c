#define ROTL(i, n, max) ((i) << (n) | (i) >> (max) - (n))
#define ROTR(i, n, max) ((i) >> (n) | (i) << (max) - (n))

// rotates `selmon->tagset[selmon->seltags]` by arg->i
// arg->i >= 0: rotate left
// arg->i < 0: rotate right
void
shiftview(const Arg *const arg)
{
	const size_t taglen = LENGTH(tags);
	const unsigned seltags = selmon->tagset[selmon->seltags] & ~SPTAGMASK;

	const Arg shifted = (Arg){
		.ui = (arg->i >= 0 ?  ROTL(seltags, arg->i, taglen) : ROTR(seltags, -arg->i, taglen)) & ~SPTAGMASK
	};

	view(&shifted);
}

#undef ROTL
#undef ROTR
