/* Process model C form file: AN_prc2.pr.c */
/* Portions of this file copyright 1992-2002 by OPNET Technologies, Inc. */



/* This variable carries the header into the object file */
static const char AN_prc2_pr_c [] = "MIL_3_Tfile_Hdr_ 81A 30A modeler 7 476D845D 476D845D 1 os_4 for@azar 0 0 none none 0 0 none 0 0 0 0 0 0                                                                                                                                                                                                                                                                                                                                                                                                                        ";
#include <string.h>



/* OPNET system definitions */
#include <opnet.h>

#if defined (__cplusplus)
extern "C" {
#endif
FSM_EXT_DECS
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif


/* Header Block */

//constants
#define  WINDOWSIZE  5
#define  NeibSize   2 
#define  VERYLARGE  1000 
#define  ETHA  0.5
#define  c1    0.7
#define  c2    0.3
#define  GAMA  0.75
#define  a     0.5
 

#define  DATA_PACKET  0
#define  FORWARD_ANT_PACKET   1
#define  BACKWARD_ANT_PACKET  2

#define  INPUT_rcv1    0
#define  INPUT_rcv2    1
#define  INPUT_dataSrc 2
#define  INPUT_antSrc  3
#define  OUTPUT_trn1   0
#define  OUTPUT_trn2   1 


//Types
typedef  struct {int index; double arr[WINDOWSIZE]; } window;
typedef  struct {double mean; double variance;  window w; } sModel;

 
//Macros
#define  PACKET_ARRIVAL  ( op_intrpt_type() == OPC_INTRPT_STRM )


//includes
#include<math.h>

/* End of Header Block */


#if !defined (VOSD_NO_FIN)
#undef	BIN
#undef	BOUT
#define	BIN		FIN_LOCAL_FIELD(last_line_passed) = __LINE__ - _block_origin;
#define	BOUT	BIN
#define	BINIT	FIN_LOCAL_FIELD(last_line_passed) = 0; _block_origin = __LINE__;
#else
#define	BINIT
#endif /* #if !defined (VOSD_NO_FIN) */



/* State variable definitions */
typedef struct
	{
	/* Internal state tracking for FSM */
	FSM_SYS_STATE
	/* State Variables */
	double	                 		routingTable[8][2];
	sModel	                 		M[8];
	Objid	                  		own_id;
	int	                    		myIP;
	} AN_prc2_state;

#define pr_state_ptr            		((AN_prc2_state*) SimI_Mod_State_Ptr)
#define routingTable            		pr_state_ptr->routingTable
#define M                       		pr_state_ptr->M
#define own_id                  		pr_state_ptr->own_id
#define myIP                    		pr_state_ptr->myIP

/* This macro definition will define a local variable called	*/
/* "op_sv_ptr" in each function containing a FIN statement.	*/
/* This variable points to the state variable data structure,	*/
/* and can be used from a C debugger to display their values.	*/
#undef FIN_PREAMBLE
#define FIN_PREAMBLE	AN_prc2_state *op_sv_ptr = pr_state_ptr;


/* Function Block */

enum { _block_origin = __LINE__ };

void topS(Packet *packet, int *addr, double *time, int *port, int *outputPort) {

   int sp =0;
   op_pk_nfd_get(packet, "SP", &sp);
   
 //  printf("In topS() SP is %d \n", sp);
   
   switch (sp) {
     
     case 1:
     op_pk_nfd_get(packet, "router1", addr);
     op_pk_nfd_get(packet, "time1", time);
	 op_pk_nfd_get(packet, "port1", port);
	 op_pk_nfd_get(packet, "outputPort1", outputPort);
	 break;
	 case 2:
	 op_pk_nfd_get(packet, "router2", addr);
     op_pk_nfd_get(packet, "time2", time);
	 op_pk_nfd_get(packet, "port2", port);
	 op_pk_nfd_get(packet, "outputPort2", outputPort);
	 break;
	 case 3:
	 op_pk_nfd_get(packet, "router3", addr);
     op_pk_nfd_get(packet, "time3", time);
	 op_pk_nfd_get(packet, "port3", port);
	 op_pk_nfd_get(packet, "outputPort3", outputPort);
	 break;
	 case 4:
	 op_pk_nfd_get(packet, "router4", addr);
     op_pk_nfd_get(packet, "time4", time);
	 op_pk_nfd_get(packet, "port4", port);
	 op_pk_nfd_get(packet, "outputPort4", outputPort);
	 break;
	 case 5:
	 op_pk_nfd_get(packet, "router5", addr);
     op_pk_nfd_get(packet, "time5", time);
	 op_pk_nfd_get(packet, "port5", port);
	 op_pk_nfd_get(packet, "outputPort5", outputPort);
	 break;
	 case 6:
	 op_pk_nfd_get(packet, "router6", addr);
     op_pk_nfd_get(packet, "time6", time);
	 op_pk_nfd_get(packet, "port6", port);
	 op_pk_nfd_get(packet, "outputPort6", outputPort);
	 break;
	 case 7:
	 op_pk_nfd_get(packet, "router7", addr);
     op_pk_nfd_get(packet, "time7", time);
	 op_pk_nfd_get(packet, "port7", port);
	 op_pk_nfd_get(packet, "outputPort7", outputPort);
	 break;
	 case 8:
	 op_pk_nfd_get(packet, "router8", addr);
     op_pk_nfd_get(packet, "time8", time);
	 op_pk_nfd_get(packet, "port8", port);
	 op_pk_nfd_get(packet, "outputPort8", outputPort);
	 break;
	 default:
	 printf("tops() error in sp value= %d\n", sp);
	 break;
	 }	 
 }
//********************************************************   
 void popS(Packet *packet, int *addr, double *time, int *port, int *outputPort) {

   int sp = 0;
   op_pk_nfd_get(packet, "SP", &sp);
   
//   printf("In popS() SP is %d \n", sp);
   
   switch (sp) {
     
     case 1:
     op_pk_nfd_get(packet, "router1", addr);
     op_pk_nfd_get(packet, "time1", time);
	 op_pk_nfd_get(packet, "port1", port);
	 op_pk_nfd_get(packet, "outputPort1", outputPort);
	 break;
	 case 2:
	 op_pk_nfd_get(packet, "router2", addr);
     op_pk_nfd_get(packet, "time2", time);
	 op_pk_nfd_get(packet, "port2", port);
	 op_pk_nfd_get(packet, "outputPort2", outputPort);
	 break;
	 case 3:
	 op_pk_nfd_get(packet, "router3", addr);
     op_pk_nfd_get(packet, "time3", time);
	 op_pk_nfd_get(packet, "port3", port);
	 op_pk_nfd_get(packet, "outputPort3", outputPort);
	 break;
	 case 4:
	 op_pk_nfd_get(packet, "router4", addr);
     op_pk_nfd_get(packet, "time4", time);
	 op_pk_nfd_get(packet, "port4", port);
	 op_pk_nfd_get(packet, "outputPort4", outputPort);
	 break;
	 case 5:
	 op_pk_nfd_get(packet, "router5", addr);
     op_pk_nfd_get(packet, "time5", time);
	 op_pk_nfd_get(packet, "port5", port);
	 op_pk_nfd_get(packet, "outputPort5", outputPort);
	 break;
	 case 6:
	 op_pk_nfd_get(packet, "router6", addr);
     op_pk_nfd_get(packet, "time6", time);
	 op_pk_nfd_get(packet, "port6", port);
	 op_pk_nfd_get(packet, "outputPort6", outputPort);
	 break;
	 case 7:
	 op_pk_nfd_get(packet, "router7", addr);
     op_pk_nfd_get(packet, "time7", time);
	 op_pk_nfd_get(packet, "port7", port);
	 op_pk_nfd_get(packet, "outputPort7", outputPort);
	 break;
	 case 8:
	 op_pk_nfd_get(packet, "router8", addr);
     op_pk_nfd_get(packet, "time8", time);
	 op_pk_nfd_get(packet, "port8", port);
	 op_pk_nfd_get(packet, "outputPort8", outputPort);
	 break;
	 default:
	 printf("pops() error in SP value= %d\n", sp);
	 break;
	 }
   
   op_pk_nfd_set(packet, "SP", sp-1);
	 
 }
//********************************************************  
 void pushS(Packet *packet, int addr, double time, int port, int outputPort) {

   int sp = 0;
   op_pk_nfd_get(packet, "SP", &sp);
   sp++;
   op_pk_nfd_set(packet, "SP", sp);
   
 //  printf("In pushS() SP is %d \n", sp+1);
   
   switch (sp) {
     
     case 1:
     op_pk_nfd_set(packet, "router1", addr);
     op_pk_nfd_set(packet, "time1", time);
	 op_pk_nfd_set(packet, "port1", port);
	 op_pk_nfd_set(packet, "outputPort1", outputPort);
	 break;
	 case 2:
	 op_pk_nfd_set(packet, "router2", addr);
     op_pk_nfd_set(packet, "time2", time);
	 op_pk_nfd_set(packet, "port2", port);
	 op_pk_nfd_set(packet, "outputPort2", outputPort);
	 break;
	 case 3:
	 op_pk_nfd_set(packet, "router3", addr);
     op_pk_nfd_set(packet, "time3", time);
	 op_pk_nfd_set(packet, "port3", port);
	 op_pk_nfd_set(packet, "outputPort3", outputPort);
	 break;
	 case 4:
	 op_pk_nfd_set(packet, "router4", addr);
     op_pk_nfd_set(packet, "time4", time);
	 op_pk_nfd_set(packet, "port4", port);
	 op_pk_nfd_set(packet, "outputPort4", outputPort);
	 break;
	 case 5:
	 op_pk_nfd_set(packet, "router5", addr);
     op_pk_nfd_set(packet, "time5", time);
	 op_pk_nfd_set(packet, "port5", port);
	 op_pk_nfd_set(packet, "outputPort5", outputPort);
	 break;
	 case 6:
	 op_pk_nfd_set(packet, "router6", addr);
     op_pk_nfd_set(packet, "time6", time);
	 op_pk_nfd_set(packet, "port6", port);
	 op_pk_nfd_set(packet, "outputPort6", outputPort);
	 break;
	 case 7:
	 op_pk_nfd_set(packet, "router7", addr);
     op_pk_nfd_set(packet, "time7", time);
	 op_pk_nfd_set(packet, "port7", port);
	 op_pk_nfd_set(packet, "outputPort7", outputPort);
	 break;
	 case 8:
	 op_pk_nfd_set(packet, "router8", addr);
     op_pk_nfd_set(packet, "time8", time);
	 op_pk_nfd_set(packet, "port8", port);
	 op_pk_nfd_set(packet, "outputPort8", outputPort);
	 break;
	 default:
	 printf("pushs() error in sp value=%d \n", sp);
	 break;
	 }
  }
 //*******************************************************
 void assingDestinationAddress(Packet *packet ){

     int destAddr = 0;
	 
	 destAddr = (int) ( ( (8-1) * op_dist_uniform(1) ) + 1);
	        //printf("%d\n",destAddr ); 
	 while ( destAddr == myIP)
		 destAddr = (int) ( ( (8-1) * op_dist_uniform(1) ) + 1);
	 
	 op_pk_nfd_set(packet, "destAddr", destAddr);
    
}
//********************************************************
void destroyPacket(Packet *packet) {

     op_pk_destroy(packet);

}
//********************************************************
void setPacketType(Packet *packet, int type){

     op_pk_nfd_set(packet, "packetType", type);

}
//********************************************************
void sendAntPacketOutProb(Packet *packet) {

   
   int dummyAddr;
   double dummyTime;
   int dummyPort;
   int outputPort;


   int destAddr=0;
   double outPort1=0;
   double outPort2=0;
   double minValue ,temp;
   int minIndex, maxIndex;
   
   //extract dest addr of packet
   op_pk_nfd_get (packet, "destAddr", &destAddr);
   outPort1 = routingTable[destAddr-1][OUTPUT_trn1];
   outPort2 = routingTable[destAddr-1][OUTPUT_trn2];
   
//   printf("In node %d outPort1 = %f and outport2 = %f \n", myIP, outPort1, outPort2);
   
   //calculate the output port prob. 
   if ( outPort1 <= outPort2 ) {
      minValue = outPort1;
	  minIndex = OUTPUT_trn1;
	  maxIndex = OUTPUT_trn2;
	  
   }	  
   else {
      minValue = outPort2;
	  minIndex = OUTPUT_trn2;
	  maxIndex = OUTPUT_trn1;
   }	  
   
   temp = op_dist_uniform(1);
   
   
   //in entrance, we saved some info, here we pop() them, add the selected port, then push() again
   popS(packet, &dummyAddr, &dummyTime, &dummyPort, &outputPort);
      
   
   if (temp <= minValue ) {
   
      outputPort = minIndex;
	  pushS(packet, dummyAddr, dummyTime, dummyPort, outputPort);
	  op_pk_send(packet, outputPort);
	  }
   else {
    
      outputPort = maxIndex;
	  pushS(packet, dummyAddr, dummyTime, dummyPort, outputPort);
	  op_pk_send(packet,outputPort);
	  }
   
  // printf("In node %d outputPort in sendAntProb() is %d \n", myIP, outputPort);
   
   //TODO: we should check the existence of loop,etc.
   
}
//********************************************************
void sendDataPacketOutProb(Packet *packet) {

   int destAddr = 0;
   double outPort1=0;
   double outPort2=0;
   double minValue, temp;
   int minIndex, maxIndex;
      
   //extract dest addr of packet
   op_pk_nfd_get (packet, "destAddr", &destAddr);
   outPort1 = routingTable[destAddr-1][OUTPUT_trn1];
   outPort2 = routingTable[destAddr-1][OUTPUT_trn2];
   
   //calculate the output port prob. 
   if ( outPort1 <= outPort2 ) {
      minValue = outPort1;
	  minIndex = OUTPUT_trn1;
	  maxIndex = OUTPUT_trn2;
	  
   }	  
   else {
      minValue = outPort2;
	  minIndex = OUTPUT_trn2;
	  maxIndex = OUTPUT_trn1;
   }	  
   
   temp = op_dist_uniform(1);
   
   
   if (temp <= minValue ) {
   
      op_pk_send(packet, minIndex);
	  }
   else {
    
      op_pk_send(packet, maxIndex);
	  }
   
}
//********************************************************	
int  getCounterpartOutPort(int stream) {

     switch (stream) {
	 
	 case INPUT_rcv1: return OUTPUT_trn1;
	 case INPUT_rcv2: return OUTPUT_trn2;
	 default: return OUTPUT_trn1;  //Normaly this shouldn't happen!!!
	 }		 
}

//********************************************************
void addToStack(Packet *packet, int stream) {

    //we should save the port to come back, we have the input port in "stream", so we change to it's output port.
    int dummyOutputPort=0;
    int output = getCounterpartOutPort(stream);
	
	pushS(packet, myIP, op_sim_time(), output, dummyOutputPort); 
	
		
}
//********************************************************

void creatBackwardAnt(Packet *packet) {

// set packet type
   op_pk_nfd_set(packet, "packetType", BACKWARD_ANT_PACKET);  
   
   }
//********************************************************
void sendOutAccordingToStack(Packet *packet) {
  
//here we should popS()
    int dummyAddr=0;
	double dummyTime=0;
	int port=0;
	int dummyOutputPort=0;
	popS (packet, &dummyAddr, &dummyTime, &port, &dummyOutputPort);
	
	op_pk_send(packet, port);
	

}
//********************************************************
double findWbest(int dest){

   int i = 0;
   double min = VERYLARGE;
   for (i=0; i<WINDOWSIZE; ++i){
      
      if (M[dest].w.arr[i] < min)
		  
		  min = M[dest].w.arr[i];
   }	
   
//   printf("In findWbest() the min value = %f\n", min);
   
   return min;
}
//********************************************************
double S(double x){

    return 1 / ( 1 + exp(a / x * NeibSize) );

}
//********************************************************
void updateTables(Packet *packet) {

    //here we should topS()
    int dummyAddr;
	double time;
	int dummyPort;
	int outputPort;
	
	double tripTime, arrivalTime;
	int dest;
		
	double r, Iinf, Isup, Wbest, z;
	
	int otherPort;
	
	topS(packet, &dummyAddr, &time, &dummyPort, &outputPort);
	otherPort = 1 - outputPort;
	
    //1- update statistic table
	op_pk_nfd_get(packet, "arrivalTime", &arrivalTime);
    tripTime = arrivalTime - time;
	op_pk_nfd_get(packet, "destAddr", &dest);
	--dest;
	
	
	M[dest].mean = (M[dest].mean) + (ETHA * (tripTime - M[dest].mean));
	M[dest].variance = M[dest].variance + ETHA * ( pow( (tripTime - M[dest].mean),2 ) - M[dest].variance );
    M[dest].w.index = M[dest].w.index + 1;
	M[dest].w.arr[  M[dest].w.index  % WINDOWSIZE ] = tripTime;
	
	//2- update routing table
	Wbest = findWbest(dest);
	
		
	Iinf = Wbest;
	//z = 1 / sqrt(1-GAMA);
	z = 1 / 0.707;
		
	
	Isup = M[dest].mean + z * ( (sqrt(M[dest].variance)) / sqrt(WINDOWSIZE));
	r = (c1 * Wbest / tripTime) + (c2 * ( (Isup-Iinf) / ((Isup-Iinf) + (tripTime-Iinf)) ));
	r = S(r) / S(1);
	if ( r >= 1 )  r = 0.999999;
	
	printf("\n**********In node %d***********\n", myIP);
	printf("before: routingtable[%d] = %f\n ",outputPort, routingTable[dest][outputPort]);
	printf("before: routingtable[%d] = %f\n ",otherPort, routingTable[dest][otherPort]);
	
    //2-1- the port that we leaved the router
    routingTable[dest][outputPort] = routingTable[dest][outputPort] + r * (1-routingTable[dest][outputPort]);								   
    //2-2- the other port
    routingTable[dest][otherPort] = routingTable[dest][otherPort] - r * routingTable[dest][otherPort];								       								   
	
	
	printf("M[%d].mean = %d\n",dest, M[dest].mean);
	printf("M[%d].variance = %d\n",dest, M[dest].variance);
	//printf("new value of window = %f\n", M[dest].w.arr[  M[dest].w.index  % WINDOWSIZE ]);
	//printf("PassTime = %f\n", time);
	//printf("tripTime = %f\n", tripTime);
	printf("r = %f\n", r);
	printf("routingTable[%d][%d] = %f\n", dest, outputPort, routingTable[dest][outputPort]);
	printf("routingTable[%d][%d] = %f\n", dest, otherPort, routingTable[dest][otherPort]);
	printf("*********************************\n");
	
}
//********************************************************
//Note: in entrance to a router, in return, we first update tables with t, so we top(), and after it, we pop() to gain the appropriate port.

/* End of Function Block */

/* Undefine optional tracing in FIN/FOUT/FRET */
/* The FSM has its own tracing code and the other */
/* functions should not have any tracing.		  */
#undef FIN_TRACING
#define FIN_TRACING

#undef FOUTRET_TRACING
#define FOUTRET_TRACING

#if defined (__cplusplus)
extern "C" {
#endif
	void AN_prc2 (void);
	Compcode AN_prc2_init (void **);
	void AN_prc2_diag (void);
	void AN_prc2_terminate (void);
	void AN_prc2_svar (void *, const char *, char **);
#if defined (__cplusplus)
} /* end of 'extern "C"' */
#endif




/* Process model interrupt handling procedure */


void
AN_prc2 (void)
	{
	int _block_origin = 0;
	FIN (AN_prc2 ());
	if (1)
		{
		int stream=0 ;
		Packet *packet=NULL;
		int packetType=0;
		
		int packetDestAddr=0;
		int antPacketSrcAddr=0;


		FSM_ENTER (AN_prc2)

		FSM_BLOCK_SWITCH
			{
			/*---------------------------------------------------------*/
			/** state (idle) enter executives **/
			FSM_STATE_ENTER_UNFORCED (0, state0_enter_exec, "idle", "AN_prc2 () [idle enter execs]")
				{
				}


			/** blocking after enter executives of unforced state. **/
			FSM_EXIT (1,AN_prc2)


			/** state (idle) exit executives **/
			FSM_STATE_EXIT_UNFORCED (0, "idle", "AN_prc2 () [idle exit execs]")
				{
				}


			/** state (idle) transition processing **/
			FSM_INIT_COND (PACKET_ARRIVAL)
			FSM_DFLT_COND
			FSM_TEST_LOGIC ("idle")

			FSM_TRANSIT_SWITCH
				{
				FSM_CASE_TRANSIT (0, 2, state2_enter_exec, ;, "PACKET_ARRIVAL", "", "idle", "rcv")
				FSM_CASE_TRANSIT (1, 0, state0_enter_exec, ;, "default", "", "idle", "idle")
				}
				/*---------------------------------------------------------*/



			/** state (init) enter executives **/
			FSM_STATE_ENTER_FORCED_NOLABEL (1, "init", "AN_prc2 () [init enter execs]")
				{
				//init the routing and statistics tables
				int i = 0;
				int j = 0;
				
				for (i=0; i<8; ++i)
					for (j=0; j<2; ++j)
						routingTable[i][j] = 0.5;
				
				for (i=0; i<8; ++i){
				
				    M[i].mean =0;
					M[i].variance =0;
					M[i].w.index = -1;
					for(j=0; j<WINDOWSIZE; ++j)
				    
						 M[i].w.arr[j] =VERYLARGE;
				}	
				
				}


			/** state (init) exit executives **/
			FSM_STATE_EXIT_FORCED (1, "init", "AN_prc2 () [init exit execs]")
				{
				}


			/** state (init) transition processing **/
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "init", "idle")
				/*---------------------------------------------------------*/



			/** state (rcv) enter executives **/
			FSM_STATE_ENTER_FORCED (2, state2_enter_exec, "rcv", "AN_prc2 () [rcv enter execs]")
				{
				
				stream = op_intrpt_strm();
				packet = op_pk_get(stream);
				
				
				//first check if the packet is a home generated one or no
				//if it's an forward ant:
				if(stream == INPUT_antSrc) {
				
				   op_pk_nfd_set(packet, "srcAddr", myIP);
				   op_pk_nfd_set(packet, "SP", 0);
				   setPacketType(packet, FORWARD_ANT_PACKET);
				   assingDestinationAddress(packet);
				   
				  }	
				
				//if it's a data packet:
				if (stream == INPUT_dataSrc) {
				
				   setPacketType(packet, DATA_PACKET);
				   assingDestinationAddress(packet);
				   
				 }
				
				//find the packet type
				op_pk_nfd_get (packet, "packetType", &packetType);
				
				//find the destination IP address of packet
				op_pk_nfd_get ( packet, "destAddr", &packetDestAddr);
				
				 
				//find self IP :D
				own_id = op_id_self ();
				op_ima_obj_attr_get (own_id, "IP", &myIP);
				
				           //printf("in node %d , packetType is %d , and destAddr is %d  \n", myIP,packetType,packetDestAddr );
					 
				//Then, first check for packet type
				//Next, for destination address
				if( packetType == DATA_PACKET ) {
				
				   if( myIP == packetDestAddr ){
				   
				//       printf("In node %d data packet recieved with destAddr = %d\n", myIP, packetDestAddr);
				       destroyPacket(packet);
					}
				   else{
				   
				       sendDataPacketOutProb(packet);
				   }	   
				}
				
				else if ( packetType == FORWARD_ANT_PACKET ) {
				
				 //Instead of removing loops, if the stack isn't full,continue. Else, finish!!!
				 int sp;
				 op_pk_nfd_get(packet, "SP", &sp);
				 
				  
				 if ( sp < 8) {
				
				    //at the entrance, first save the arrival time to this node & node IP & the port in the stack
				    addToStack(packet, stream);
					
				    if( myIP == packetDestAddr ){
				   
				     //  arrivalTime = op_sim_time();
					   op_pk_nfd_set(packet, "arrivalTime", op_sim_time() );
				       creatBackwardAnt(packet);
					   sendOutAccordingToStack(packet);
				    }
				    else{
				      
				        sendAntPacketOutProb(packet);
				    }
					
				 }
				 
				 else {
				 
				    printf("In node with IP %d, the SP of a forward ant was %d, so did nothing!\n", myIP, sp); 
					destroyPacket(packet);
				}	
				 
				}
				
				else if ( packetType == BACKWARD_ANT_PACKET ) {
				
				   //printf("An Backward Ant Packet recieved. \n"); 
				   updateTables(packet);
				   
				   op_pk_nfd_get(packet, "srcAddr", &antPacketSrcAddr); 
				   if( myIP ==  antPacketSrcAddr ){
				    
				      printf("Home! backward ant with srcAddr = %d and myIP = %d\n" ,antPacketSrcAddr, myIP); 
				      destroyPacket(packet); 
				   }
				   else
					    
				      sendOutAccordingToStack(packet);
				}
				
				else {
				   printf("ERROR IN PACKET TYPE\n");
				}
					
					
					
				}


			/** state (rcv) exit executives **/
			FSM_STATE_EXIT_FORCED (2, "rcv", "AN_prc2 () [rcv exit execs]")
				{
				}


			/** state (rcv) transition processing **/
			FSM_TRANSIT_FORCE (0, state0_enter_exec, ;, "default", "", "rcv", "idle")
				/*---------------------------------------------------------*/



			}


		FSM_EXIT (1,AN_prc2)
		}
	}

#if defined (__cplusplus)
	extern "C" { 
#endif
	extern VosT_Fun_Status Vos_Catmem_Register (const char * , int , VosT_Void_Null_Proc, VosT_Address *);
	extern VosT_Address Vos_Catmem_Alloc (VosT_Address, size_t);
	extern VosT_Fun_Status Vos_Catmem_Dealloc (VosT_Address);
#if defined (__cplusplus)
	}
#endif


Compcode
AN_prc2_init (void ** gen_state_pptr)
	{
	int _block_origin = 0;
	static VosT_Address	obtype = OPC_NIL;

	FIN (AN_prc2_init (gen_state_pptr))

	if (obtype == OPC_NIL)
		{
		/* Initialize memory management */
		if (Vos_Catmem_Register ("proc state vars (AN_prc2)",
			sizeof (AN_prc2_state), Vos_Vnop, &obtype) == VOSC_FAILURE)
			{
			FRET (OPC_COMPCODE_FAILURE)
			}
		}

	*gen_state_pptr = Vos_Catmem_Alloc (obtype, 1);
	if (*gen_state_pptr == OPC_NIL)
		{
		FRET (OPC_COMPCODE_FAILURE)
		}
	else
		{
		/* Initialize FSM handling */
		((AN_prc2_state *)(*gen_state_pptr))->current_block = 2;

		FRET (OPC_COMPCODE_SUCCESS)
		}
	}



void
AN_prc2_diag (void)
	{
	/* No Diagnostic Block */
	}




void
AN_prc2_terminate (void)
	{
	int _block_origin = __LINE__;

	FIN (AN_prc2_terminate (void))

	Vos_Catmem_Dealloc (pr_state_ptr);

	FOUT;
	}


/* Undefine shortcuts to state variables to avoid */
/* syntax error in direct access to fields of */
/* local variable prs_ptr in AN_prc2_svar function. */
#undef routingTable
#undef M
#undef own_id
#undef myIP



void
AN_prc2_svar (void * gen_ptr, const char * var_name, char ** var_p_ptr)
	{
	AN_prc2_state		*prs_ptr;

	FIN (AN_prc2_svar (gen_ptr, var_name, var_p_ptr))

	if (var_name == OPC_NIL)
		{
		*var_p_ptr = (char *)OPC_NIL;
		FOUT;
		}
	prs_ptr = (AN_prc2_state *)gen_ptr;

	if (strcmp ("routingTable" , var_name) == 0)
		{
		*var_p_ptr = (char *) (prs_ptr->routingTable);
		FOUT;
		}
	if (strcmp ("M" , var_name) == 0)
		{
		*var_p_ptr = (char *) (prs_ptr->M);
		FOUT;
		}
	if (strcmp ("own_id" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->own_id);
		FOUT;
		}
	if (strcmp ("myIP" , var_name) == 0)
		{
		*var_p_ptr = (char *) (&prs_ptr->myIP);
		FOUT;
		}
	*var_p_ptr = (char *)OPC_NIL;

	FOUT;
	}

