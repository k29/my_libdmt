
/**
 * \brief  Unrandomize 255 state
 * \param  value
 * \param  idx
 * \return Unrandomized value
 */
static unsigned char
UnRandomize255State(unsigned char value, int idx)
{
   int pseudoRandom;
   int tmp;

   pseudoRandom = ((149 * idx) % 255) + 1;
   tmp = value - pseudoRandom;
   if(tmp < 0)
      tmp += 256;

   assert(tmp >= 0 && tmp < 256);

   return (unsigned char)tmp;
}
