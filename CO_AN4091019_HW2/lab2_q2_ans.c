// TODO : 
"addi t1, x0, 8\n\t"        // loop counter & arrsize
"vsetvli t0, t1, e16\n\t"
"vle16.v v0, (%[p_x])\n\t"
"loop:\n\t"
"lw t2, 0(%[p_x])\n\t"  // load the x[i]
"vadd.vx v1, v0, t2\n\t"    //  v1[j] = x[j] + x[i] 
"vmseq.vx v2, v1, %[target]\n\t"    // set v2[0] if v1[j] = target
"vfirst.m t3, v2\n\t"   // find first set bit
"bltz t3, skip\n\t"
"addi %[flag], %[flag], 1\n\t"
"j found\n\t"
"skip:\n\t"
"addi %[p_x], %[p_x], 2\n\t"
"addi t1, t1,-1\n\t"
"bnez t1, loop\n\t"
"found:\n\t"
"vse16.v v2, (%[p_tmp1])\n\t"