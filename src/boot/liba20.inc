a20_status:
      mov ax, 2402h
      int 15h
      ret
      
a20_enable:
      call a20_status
      cmp al, 1
      je .done
      mov ax, 2401h
      int 15h
      .done:
	    ret
	    
a20_disable:	    
      call a20_status
      cmp al, 0
      je .done
      mov ax, 2400h
      int 15h
      .done:
	    ret
	    