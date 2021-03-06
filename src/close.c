#include <linux/kernel.h>

#include <linux/net.h>
#include <linux/socket.h>
#include <net/tcp.h>

#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

#include "ulp.h"
#include "pool.h"
#include "syscalls.h"

void ulp_close(struct sock *sk, long int timeout)
{
   /* We need to NULL icsk_ulp_ops to prevent module_put call
    * inside tcp_ulp.c.
    */
   if (sk->sk_state != TCP_LISTEN)
      inet_csk(sk)->icsk_ulp_ops = NULL;

   sk_cleanup_ulp_data(sk);
   sk->sk_prot = sys;

   sys->close(sk, timeout);
}
