/*******************************************************************************

    Copyright 2013-2014 Ben Wojtowicz

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Affero General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Affero General Public License for more details.

    You should have received a copy of the GNU Affero General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

*******************************************************************************

    File: LTE_fdd_enb_pdcp.h

    Description: Contains all the definitions for the LTE FDD eNodeB
                 packet data convergence protocol layer.

    Revision History
    ----------    -------------    --------------------------------------------
    11/09/2013    Ben Wojtowicz    Created file
    05/04/2014    Ben Wojtowicz    Added communication to RLC and RRC.
    11/29/2014    Ben Wojtowicz    Added communication to IP gateway.

*******************************************************************************/

#ifndef __LTE_FDD_ENB_PDCP_H__
#define __LTE_FDD_ENB_PDCP_H__

/*******************************************************************************
                              INCLUDES
*******************************************************************************/

#include "LTE_fdd_enb_cnfg_db.h"
#include "LTE_fdd_enb_msgq.h"
#include <boost/thread/mutex.hpp>
#include <boost/interprocess/ipc/message_queue.hpp>

/*******************************************************************************
                              DEFINES
*******************************************************************************/


/*******************************************************************************
                              FORWARD DECLARATIONS
*******************************************************************************/


/*******************************************************************************
                              TYPEDEFS
*******************************************************************************/


/*******************************************************************************
                              CLASS DECLARATIONS
*******************************************************************************/

class LTE_fdd_enb_pdcp
{
public:
    // Singleton
    static LTE_fdd_enb_pdcp* get_instance(void);
    static void cleanup(void);

    // Start/Stop
    void start(void);
    void stop(void);

    // External interface
    void update_sys_info(void);

private:
    // Singleton
    static LTE_fdd_enb_pdcp *instance;
    LTE_fdd_enb_pdcp();
    ~LTE_fdd_enb_pdcp();

    // Start/Stop
    boost::mutex start_mutex;
    bool         started;

    // Communication
    void handle_rlc_msg(LTE_FDD_ENB_MESSAGE_STRUCT *msg);
    void handle_rrc_msg(LTE_FDD_ENB_MESSAGE_STRUCT *msg);
    void handle_gw_msg(LTE_FDD_ENB_MESSAGE_STRUCT *msg);
    LTE_fdd_enb_msgq                   *rlc_comm_msgq;
    LTE_fdd_enb_msgq                   *rrc_comm_msgq;
    LTE_fdd_enb_msgq                   *gw_comm_msgq;
    boost::interprocess::message_queue *pdcp_rlc_mq;
    boost::interprocess::message_queue *pdcp_rrc_mq;
    boost::interprocess::message_queue *pdcp_gw_mq;

    // RLC Message Handlers
    void handle_pdu_ready(LTE_FDD_ENB_PDCP_PDU_READY_MSG_STRUCT *pdu_ready);

    // RRC Message Handlers
    void handle_sdu_ready(LTE_FDD_ENB_PDCP_SDU_READY_MSG_STRUCT *sdu_ready);

    // GW Message Handlers
    void handle_data_sdu_ready(LTE_FDD_ENB_PDCP_DATA_SDU_READY_MSG_STRUCT *data_sdu_ready);

    // Parameters
    boost::mutex                sys_info_mutex;
    LTE_FDD_ENB_SYS_INFO_STRUCT sys_info;
};

#endif /* __LTE_FDD_ENB_PDCP_H__ */
