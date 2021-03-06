/** Generated by YAKINDU Statechart Tools code generator. */

#ifndef PROYECTO_H_
#define PROYECTO_H_

#ifdef __cplusplus
extern "C" { 
#endif

/*!
* Forward declaration for the Proyecto state machine.
*/
typedef struct Proyecto Proyecto;

/*!
* Forward declaration of the data structure for the ProyectoIface interface scope.
*/
typedef struct ProyectoIface ProyectoIface;

/*!
* Forward declaration of the data structure for the ProyectoInternal interface scope.
*/
typedef struct ProyectoInternal ProyectoInternal;

/*!
* Forward declaration of the data structure for the ProyectoTimeEvents interface scope.
*/
typedef struct ProyectoTimeEvents ProyectoTimeEvents;

#ifdef __cplusplus
}
#endif

#include "../../src/sc_types.h"

#ifdef __cplusplus
extern "C" { 
#endif 

/*! \file Header of the state machine 'proyecto'.
*/

#ifndef PROYECTO_EVENTQUEUE_BUFFERSIZE
#define PROYECTO_EVENTQUEUE_BUFFERSIZE 20
#endif
#ifndef PROYECTO_IN_EVENTQUEUE_BUFFERSIZE
#define PROYECTO_IN_EVENTQUEUE_BUFFERSIZE PROYECTO_EVENTQUEUE_BUFFERSIZE
#endif
#ifndef PROYECTO_INTERNAL_EVENTQUEUE_BUFFERSIZE
#define PROYECTO_INTERNAL_EVENTQUEUE_BUFFERSIZE PROYECTO_EVENTQUEUE_BUFFERSIZE
#endif
#ifndef SC_INVALID_EVENT_VALUE
#define SC_INVALID_EVENT_VALUE 0
#endif
/*! Define number of states in the state enum */
#define PROYECTO_STATE_COUNT 11

/*! Define dimension of the state configuration vector for orthogonal states. */
#define PROYECTO_MAX_ORTHOGONAL_STATES 3
/*! Define maximum number of time events that can be active at once */
#define PROYECTO_MAX_PARALLEL_TIME_EVENTS 5

/*! Define indices of states in the StateConfVector */
#define SCVI_PROYECTO_MAIN_REGION_IDLE 0
#define SCVI_PROYECTO_MAIN_REGION_FEEDING 0
#define SCVI_PROYECTO_MAIN_REGION_NO_FOOD 0
#define SCVI_PROYECTO_MAIN_REGION_PAUSED 0
#define SCVI_PROYECTO_CLK_SECONDS 1
#define SCVI_PROYECTO_CLK_MINUTES 1
#define SCVI_PROYECTO_CLK_INIT 1
#define SCVI_PROYECTO_CLK_HOURS 1
#define SCVI_PROYECTO_CLK_DAYS 1
#define SCVI_PROYECTO_CONF_IDLE 2
#define SCVI_PROYECTO_CONF_PARAMETER_SET 2


/*
 * Enum of event names in the statechart.
 */
typedef enum  {
	Proyecto_invalid_event = SC_INVALID_EVENT_VALUE,
	Proyecto_evFeed,
	Proyecto_evFeedRst,
	Proyecto_evNoFood,
	Proyecto_evConfigure,
	Proyecto_evPause,
	Proyecto_evUnpause,
	Proyecto_evIdle,
	Proyecto_internal_siFeed,
	Proyecto_proyecto_main_region_Feeding_time_event_0,
	Proyecto_proyecto_main_region_Paused_time_event_0,
	Proyecto_proyecto_clk_Seconds_time_event_0,
	Proyecto_proyecto_clk_Seconds_time_event_1,
	Proyecto_proyecto_clk_Seconds_time_event_2,
	Proyecto_proyecto_clk_Minutes_time_event_0,
	Proyecto_proyecto_clk_Minutes_time_event_1,
	Proyecto_proyecto_clk_Minutes_time_event_2,
	Proyecto_proyecto_clk_Init_time_event_0,
	Proyecto_proyecto_clk_Hours_time_event_0,
	Proyecto_proyecto_clk_Hours_time_event_1,
	Proyecto_proyecto_clk_Hours_time_event_2,
	Proyecto_proyecto_clk_Days_time_event_0,
	Proyecto_proyecto_clk_Days_time_event_1,
	Proyecto_proyecto_clk_Days_time_event_2,
	Proyecto_proyecto_conf_Parameter_Set_time_event_0
} ProyectoEventID;

/*
 * Struct that represents a single event.
 */
typedef struct {
	ProyectoEventID name;
} proyecto_event;

/*
 * Queue that holds the raised events.
 */
typedef struct proyecto_eventqueue_s {
	proyecto_event *events;
	sc_integer capacity;
	sc_integer pop_index;
	sc_integer push_index;
	sc_integer size;
} proyecto_eventqueue;

/*! Enumeration of all states */ 
typedef enum
{
	Proyecto_last_state,
	Proyecto_main_region_Idle,
	Proyecto_main_region_Feeding,
	Proyecto_main_region_No_Food,
	Proyecto_main_region_Paused,
	Proyecto_clk_Seconds,
	Proyecto_clk_Minutes,
	Proyecto_clk_Init,
	Proyecto_clk_Hours,
	Proyecto_clk_Days,
	Proyecto_conf_Idle,
	Proyecto_conf_Parameter_Set
} ProyectoStates;


/*! Type declaration of the data structure for the ProyectoIface interface scope. */
struct ProyectoIface
{
	sc_boolean evFeed_raised;
	sc_boolean evFeedRst_raised;
	sc_boolean evNoFood_raised;
	sc_boolean evConfigure_raised;
	sc_boolean evPause_raised;
	sc_boolean evUnpause_raised;
	sc_boolean evIdle_raised;
	sc_integer viIntervalHs;
	sc_integer viIntervalMin;
	sc_integer viIntervalSec;
	sc_integer viAmount;
	sc_integer viT_ON;
	sc_boolean viPaused;
};


/* Declaration of constants for scope ProyectoIface. */
extern const sc_integer PROYECTO_PROYECTOIFACE_MAX_SEC;
extern const sc_integer PROYECTO_PROYECTOIFACE_MAX_MIN;
extern const sc_integer PROYECTO_PROYECTOIFACE_MAX_HS;
extern const sc_integer PROYECTO_PROYECTOIFACE_MAX_DD;
extern const sc_integer PROYECTO_PROYECTOIFACE_NO_FOOD;
extern const sc_integer PROYECTO_PROYECTOIFACE_OK_FOOD;
extern const sc_integer PROYECTO_PROYECTOIFACE_FLOW;


/*! Type declaration of the data structure for the ProyectoInternal interface scope. */
struct ProyectoInternal
{
	sc_integer viSec;
	sc_integer viMin;
	sc_integer viHs;
	sc_integer viDD;
	sc_boolean siFeed_raised;
};



/*! Type declaration of the data structure for the ProyectoTimeEvents interface scope. */
struct ProyectoTimeEvents
{
	sc_boolean proyecto_main_region_Feeding_tev0_raised;
	sc_boolean proyecto_main_region_Paused_tev0_raised;
	sc_boolean proyecto_clk_Seconds_tev0_raised;
	sc_boolean proyecto_clk_Seconds_tev1_raised;
	sc_boolean proyecto_clk_Seconds_tev2_raised;
	sc_boolean proyecto_clk_Minutes_tev0_raised;
	sc_boolean proyecto_clk_Minutes_tev1_raised;
	sc_boolean proyecto_clk_Minutes_tev2_raised;
	sc_boolean proyecto_clk_Init_tev0_raised;
	sc_boolean proyecto_clk_Hours_tev0_raised;
	sc_boolean proyecto_clk_Hours_tev1_raised;
	sc_boolean proyecto_clk_Hours_tev2_raised;
	sc_boolean proyecto_clk_Days_tev0_raised;
	sc_boolean proyecto_clk_Days_tev1_raised;
	sc_boolean proyecto_clk_Days_tev2_raised;
	sc_boolean proyecto_conf_Parameter_Set_tev0_raised;
};






/*! 
 * Type declaration of the data structure for the Proyecto state machine.
 * This data structure has to be allocated by the client code. 
 */
struct Proyecto
{
	ProyectoStates stateConfVector[PROYECTO_MAX_ORTHOGONAL_STATES];
	ProyectoIface iface;
	ProyectoInternal internal;
	ProyectoTimeEvents timeEvents;
	sc_boolean isExecuting;
	sc_integer stateConfVectorPosition;
	proyecto_eventqueue internal_event_queue;
	proyecto_event internal_buffer[PROYECTO_INTERNAL_EVENTQUEUE_BUFFERSIZE];
	proyecto_eventqueue in_event_queue;
	proyecto_event in_buffer[PROYECTO_IN_EVENTQUEUE_BUFFERSIZE];
};



/*! Initializes the Proyecto state machine data structures. Must be called before first usage.*/
extern void proyecto_init(Proyecto* handle);


/*! Activates the state machine. */
extern void proyecto_enter(Proyecto* handle);

/*! Deactivates the state machine. */
extern void proyecto_exit(Proyecto* handle);



/*! Raises a time event. */
extern void proyecto_raise_time_event(Proyecto* handle, sc_eventid evid);

/*! Raises the in event 'evFeed' that is defined in the default interface scope. */ 
extern void proyecto_raise_evFeed(Proyecto* handle);
/*! Raises the in event 'evFeedRst' that is defined in the default interface scope. */ 
extern void proyecto_raise_evFeedRst(Proyecto* handle);
/*! Raises the in event 'evNoFood' that is defined in the default interface scope. */ 
extern void proyecto_raise_evNoFood(Proyecto* handle);
/*! Raises the in event 'evConfigure' that is defined in the default interface scope. */ 
extern void proyecto_raise_evConfigure(Proyecto* handle);
/*! Raises the in event 'evPause' that is defined in the default interface scope. */ 
extern void proyecto_raise_evPause(Proyecto* handle);
/*! Raises the in event 'evUnpause' that is defined in the default interface scope. */ 
extern void proyecto_raise_evUnpause(Proyecto* handle);
/*! Raises the in event 'evIdle' that is defined in the default interface scope. */ 
extern void proyecto_raise_evIdle(Proyecto* handle);
/*! Gets the value of the variable 'MAX_SEC' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_mAX_SEC(const Proyecto* handle);
/*! Gets the value of the variable 'MAX_MIN' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_mAX_MIN(const Proyecto* handle);
/*! Gets the value of the variable 'MAX_HS' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_mAX_HS(const Proyecto* handle);
/*! Gets the value of the variable 'MAX_DD' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_mAX_DD(const Proyecto* handle);
/*! Gets the value of the variable 'NO_FOOD' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_nO_FOOD(const Proyecto* handle);
/*! Gets the value of the variable 'OK_FOOD' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_oK_FOOD(const Proyecto* handle);
/*! Gets the value of the variable 'FLOW' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_fLOW(const Proyecto* handle);
/*! Gets the value of the variable 'viIntervalHs' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_viIntervalHs(const Proyecto* handle);
/*! Sets the value of the variable 'viIntervalHs' that is defined in the default interface scope. */ 
extern void proyecto_set_viIntervalHs(Proyecto* handle, sc_integer value);
/*! Gets the value of the variable 'viIntervalMin' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_viIntervalMin(const Proyecto* handle);
/*! Sets the value of the variable 'viIntervalMin' that is defined in the default interface scope. */ 
extern void proyecto_set_viIntervalMin(Proyecto* handle, sc_integer value);
/*! Gets the value of the variable 'viIntervalSec' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_viIntervalSec(const Proyecto* handle);
/*! Sets the value of the variable 'viIntervalSec' that is defined in the default interface scope. */ 
extern void proyecto_set_viIntervalSec(Proyecto* handle, sc_integer value);
/*! Gets the value of the variable 'viAmount' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_viAmount(const Proyecto* handle);
/*! Sets the value of the variable 'viAmount' that is defined in the default interface scope. */ 
extern void proyecto_set_viAmount(Proyecto* handle, sc_integer value);
/*! Gets the value of the variable 'viT_ON' that is defined in the default interface scope. */ 
extern sc_integer proyecto_get_viT_ON(const Proyecto* handle);
/*! Sets the value of the variable 'viT_ON' that is defined in the default interface scope. */ 
extern void proyecto_set_viT_ON(Proyecto* handle, sc_integer value);
/*! Gets the value of the variable 'viPaused' that is defined in the default interface scope. */ 
extern sc_boolean proyecto_get_viPaused(const Proyecto* handle);
/*! Sets the value of the variable 'viPaused' that is defined in the default interface scope. */ 
extern void proyecto_set_viPaused(Proyecto* handle, sc_boolean value);

/*!
 * Checks whether the state machine is active (until 2.4.1 this method was used for states).
 * A state machine is active if it was entered. It is inactive if it has not been entered at all or if it has been exited.
 */
extern sc_boolean proyecto_is_active(const Proyecto* handle);

/*!
 * Checks if all active states are final. 
 * If there are no active states then the state machine is considered being inactive. In this case this method returns false.
 */
extern sc_boolean proyecto_is_final(const Proyecto* handle);

/*! Checks if the specified state is active (until 2.4.1 the used method for states was called isActive()). */
extern sc_boolean proyecto_is_state_active(const Proyecto* handle, ProyectoStates state);


#ifdef __cplusplus
}
#endif 

#endif /* PROYECTO_H_ */
