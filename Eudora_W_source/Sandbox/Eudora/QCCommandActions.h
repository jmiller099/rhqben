#ifndef QCCOMMANDACTIONS_H
#define QCCOMMANDACTIONS_H

enum COMMAND_ACTION_TYPE
{
	CA_NONE,
	CA_NEW,
	CA_RENAME,
	CA_DELETE,
	CA_REPLY_WITH,
	CA_NEW_MESSAGE_WITH,
	CA_NEW_MESSAGE_TO,
	CA_FORWARD_TO,
	CA_REDIRECT_TO,
	CA_INSERT_RECIPIENT,
	CA_OPEN,
 	CA_AUTO_REPLY_WITH,
	CA_TRANSFER_TO,
	CA_COPY,
	CA_GRAFT,
	CA_INSERT_FCC,
	CA_UPDATE_STATUS,
	CA_COMPACT,
	CA_ATTACH_PLUGIN,
	CA_SPECIAL_PLUGIN,
	CA_TRANSLATE_PLUGIN,
	CA_DRAW,
	CA_MEASURE,
	CA_TRANSMISSION_PLUGIN,
	CA_TOGGLE,
	CA_NEW_MAILBOX,
	CA_TRANSFER_NEW,
	CA_FCC_NEW,
	CA_FILTER_TRANSFER,
	CA_FILTER_TRANSFER_NEW,
	CA_REPLY_TO_ALL_WITH,
	CA_MAKE_FILTER_RECIP,
#ifdef IMAP4
	CA_IMAP_REFRESH,
	CA_IMAP_RESYNC,
	CA_IMAP_PROPERTIES,
	CA_DELETE_MESSAGE,
	CA_UNDELETE_MESSAGE,
	CA_EXPUNGE,
	CA_IMAP_GRAFT,
#endif // IMAP4
	CA_CHANGE_PERSONA,
	CA_SORT_AFTER_RENAME,
	// For registration/shareware manager
	CA_SWM_CHANGE_FEATURE,
	CA_SWM_CHANGE_REGCODE,
	CA_SWM_CHANGE_USERSTATE
};
#endif
