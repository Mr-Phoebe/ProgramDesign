/*********************************************
The selective repeat accepts frames out of orders but passes packets to the
network layer in order. Associated with each outstanding frame is a timer.When
timer expires,only that frame is retransmitted,not all the outstanding frames, as in protocol 5.

whn6325689
Mr.Phoebe
http://blog.csdn.net/u013007900

*******************************************************/
#include <stdio.h>
#include <string.h>
#include "protocol.h"

/************************************* 1.the data struct part **********************************/

/* set the number of window */
#define inc(k) k = (k+1)%(MAX_SEQ + 1)
/* data frame timout max time */
#define DATA_TIMER  4700

/* ack frame timeout max time*/
#define ACK_TIMER 300

/* the max seq of frame */
#define MAX_SEQ 43

/* the receiver's and sender's window buffer size */
#define NR_BUFS ((MAX_SEQ + 1) / 2)
/* illustrate the bool,let 'false' represent the number '0',let 'true' represent the number '1' */
typedef enum{ false, true }bool;

/* sequence or ack numbers */
typedef unsigned char seq_nr;

/* the defination of packet */
typedef struct{
	unsigned char info[PKT_LEN];
}packet;

/* phl_ready = 0 remarks that the physical layer is not ready yet */
static int phl_ready = 0;

/* no nak has been sent yet,use the nak only when it is the first time that the frame is error */
bool no_nak = true;

/* the defnation of the frame
DATA Frame
+=========+========+========+===============+========+
| KIND(1) | SEQ(1) | ACK(1) | DATA(240~256) | CRC(4) |
+=========+========+========+===============+========+

ACK Frame
+=========+========+========+
| KIND(1) | ACK(1) | CRC(4) |
+=========+========+========+

NAK Frame
+=========+========+========+
| KIND(1) | ACK(1) | CRC(4) |
+=========+========+========+
*/
typedef struct FRAME
{
	unsigned char kind;   /* what kind of the frame is it? */
	seq_nr ack;           /* acknowledgement number */
	seq_nr  seq;          /* sequence number */
	packet data;          /* the data transport */
	unsigned int  padding;/* the network layer packet */
}Frame;

/************************************** 2.the subfunction part ****************************************/

/* decide the window needs sliding or not */
static int between(seq_nr a, seq_nr b, seq_nr c)
{
	return((a <= b && b < c) || (c < a && a <= b) || (b < c && c < a));
}

/* send a packet to the network layer */
static void put_frame(unsigned char *frame, int len)
{
	*(unsigned int *)(frame + len) = crc32(frame, len);/* generate the check sum for the data in buffer */
	send_frame(frame, len + 4); /* send the data after generating the check sum */
	phl_ready = 0;       /* let the physical layer stay in unready */
}

static void send_data(unsigned char fk, seq_nr frame_nr, seq_nr frame_expected, packet buffer[])
{
	/* Construct and send a data, ack, or nak frame */
	Frame s;    /* scratch variable */
	s.kind = fk; /* kind == data, ack, or nak */
	s.seq = frame_nr; /* only meaningful for data frames */
	s.ack = (frame_expected + MAX_SEQ) % (MAX_SEQ + 1);/* confire the ack */

	/* if the kind of frame is data */
	if (fk == FRAME_DATA)
	{
		memcpy(s.data.info, buffer[frame_nr%NR_BUFS].info, PKT_LEN);/* copy the data to s */
		//dbg_frame("Send DATA %d %d,ID %d\n", s.seq, s.ack, *(short*)&(s.data).info);/* when the first bit of debug_mask is 0, the code is of no output */

		put_frame((unsigned char *)&s, 3 + PKT_LEN); /* send the frame to the network layer */
		start_timer(frame_nr%NR_BUFS, DATA_TIMER);   /* start the timer of data */
	}
	/* if the kind of frame is nak */
	if (fk == FRAME_NAK)
	{
		no_nak = false;    /* one nak has been sent yet */
		put_frame((unsigned char *)&s, 2);
	}
	/* if the kind of frame is ack */
	if (fk == FRAME_ACK)
	{
		//dbg_frame("Send ACK %d\n", s.ack);
		put_frame((unsigned char *)&s, 2);
	}

	stop_ack_timer(); /* no need for separate ack frame */
}

/************************************ 3.the main function part *****************************************/

int main(int argc, char **argv)
{
	seq_nr next_frame_to_send;  /* upper edge of sender's window+1 */
	seq_nr ack_expected;        /* lower edge of sender's window */
	seq_nr frame_expected;      /* lower edge of receiver's window */
	seq_nr too_far;             /* upper edge of receiver's window+1 */
	int arg, length = 0;
	int i;                      /* index into buffer pool */

	Frame r;                    /* scratch variable */
	seq_nr nbuffered;           /* the number of output buffers currently used */
	packet out_buf[NR_BUFS];    /* buffers for outbound stream */
	packet in_buf[NR_BUFS];     /* buffers for inbound stream */
	bool arrived[NR_BUFS];      /* inbound bit map */
	int event;

	enable_network_layer();     /* initialize */

	ack_expected = 0;           /* next ack expected on the inbound stream */
	next_frame_to_send = 0;     /* number of next putgoing frame */
	frame_expected = 0;         /* the number expected to receive */
	too_far = NR_BUFS;
	nbuffered = 0;              /* initially no packets are buffered */

	for (i = 0; i < NR_BUFS; i++)
	{
		arrived[i] = false; /* the i of receiver's window can receive data */
	}

	protocol_init(argc, argv);  /* the initializatio of the protocol's environment */
	lprintf("Designed by Mr.Phoebe, build: " __DATE__"  "__TIME__"\n");

	disable_network_layer();

	while (1)
	{
		event = wait_for_event(&arg);/* five possibilities */

		switch (event)
		{
			/* accept, save, and transmit a new frame */
		case NETWORK_LAYER_READY:
			nbuffered++;     /* expand the window */
			get_packet(out_buf[next_frame_to_send%NR_BUFS].info);            /* fetch the new packet */
			send_data(FRAME_DATA, next_frame_to_send, frame_expected, out_buf); /* transmit the packet */
			inc(next_frame_to_send);  /* advance upper window edge */
			break;

			/* the physical layer is ready */
		case PHYSICAL_LAYER_READY:
			phl_ready = 1;
			break;

			/* a data or control frame has arrived */
		case FRAME_RECEIVED:
			length = recv_frame((unsigned char *)&r, sizeof r);

			/* check the frame received is right or not */
			if (length < 5 || crc32((unsigned char *)&r, length) != 0)
			{
				//dbg_event("**** Receiver Error, Bad CRC ******\n");
				if (no_nak)
				{
					send_data(FRAME_NAK, 0, frame_expected, out_buf);/* send a nak */
				}
				break;
			}
			/* an undamaged frame has arrived */
			if (r.kind == FRAME_DATA)
			{
				/* check the sequence received is expected or not */
				if ((r.seq != frame_expected) && no_nak)
					send_data(FRAME_NAK, 0, frame_expected, out_buf);
				else
					start_ack_timer(ACK_TIMER);
				/* check the sequence is in the window or not */
				if (between(frame_expected, r.seq, too_far) && (arrived[r.seq%NR_BUFS] == false))
				{
					//	dbg_frame("Recv DATA %d %d,ID %d\n",r.seq,r.ack,*(short*)&(r.data).info);
					arrived[r.seq%NR_BUFS] = true; /* set the buffer '1' */
					in_buf[r.seq%NR_BUFS] = r.data;/* storage the data into the in_buff */
					/* inbound bit map */
					while (arrived[frame_expected%NR_BUFS])
					{
						/* Pass the frames and advance window */
						put_packet(in_buf[frame_expected%NR_BUFS].info, length - 7);
						no_nak = true;
						arrived[frame_expected%NR_BUFS] = false;/* set the i of receiver's window can receive frame */
						inc(frame_expected);
						inc(too_far);
						start_ack_timer(ACK_TIMER);   /* set the timer of ack */
					}
				}
			}
			/* the frame is error and resend the frame */
			if ((r.kind == FRAME_NAK) && between(ack_expected, (r.ack + 1) % (MAX_SEQ + 1), next_frame_to_send))
			{
				//	dbg_frame("Recv NAK DATA %d\n",r.ack);
				send_data(FRAME_DATA, (r.ack + 1) % (MAX_SEQ + 1), frame_expected, out_buf);
			}
			/* receive the right frame from the sender */
			while (between(ack_expected, r.ack, next_frame_to_send))
			{
				nbuffered--; /* handle piggybacked ack */
				stop_timer(ack_expected%NR_BUFS);/* frame arrived intact */
				inc(ack_expected); /* advance lower edge of sender's window */
			}
			break;

			/* the timer of ack is overtime */
		case ACK_TIMEOUT:
			//dbg_event("******** DATA %d timeout *********\n", arg);
			send_data(FRAME_ACK, 0, frame_expected, out_buf);
			break;

			/* the timer of data is overtime */
		case DATA_TIMEOUT:
			//dbg_event("******** DATA %d timeout **********\n", arg);
			if (!between(ack_expected, arg, next_frame_to_send))
				arg = arg + NR_BUFS;
			send_data(FRAME_DATA, arg, frame_expected, out_buf);
			break;

		default:
			break;
		}

		/* the buffer of receiver is full */
		if (nbuffered <NR_BUFS&& phl_ready)
			enable_network_layer();
		/* the buffer of receiver is not full */
		else
			disable_network_layer();
	}
}
