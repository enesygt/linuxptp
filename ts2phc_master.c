/**
 * @file ts2phc_master.c
 * @note Copyright (C) 2019 Richard Cochran <richardcochran@gmail.com>
 * @note SPDX-License-Identifier: GPL-2.0+
 */
#include "ts2phc.h"
#include "ts2phc_generic_master.h"
#include "ts2phc_master_private.h"
#include "ts2phc_nmea_master.h"
#include "ts2phc_phc_master.h"

struct ts2phc_master *ts2phc_master_create(struct ts2phc_private *priv,
					   const char *dev,
					   enum ts2phc_master_type type)
{
	struct ts2phc_master *master = NULL;

	switch (type) {
	case TS2PHC_MASTER_GENERIC:
		master = ts2phc_generic_master_create(priv, dev);
		break;
	case TS2PHC_MASTER_NMEA:
		master = ts2phc_nmea_master_create(priv, dev);
		break;
	case TS2PHC_MASTER_PHC:
		master = ts2phc_phc_master_create(priv, dev);
		break;
	}
	return master;
}

void ts2phc_master_destroy(struct ts2phc_master *master)
{
	master->destroy(master);
}

int ts2phc_master_getppstime(struct ts2phc_master *master, struct timespec *ts)
{
	return master->getppstime(master, ts);
}

struct clock *ts2phc_master_get_clock(struct ts2phc_master *m)
{
	if (m->get_clock)
		return m->get_clock(m);

	return NULL;
}
