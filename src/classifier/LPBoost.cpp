/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Written (W) 2007 Soeren Sonnenburg
 * Copyright (C) 2007 Fraunhofer Institute FIRST and Max-Planck-Society
 */

#include "lib/config.h"

#ifdef USE_CPLEX

#include "classifier/LPBoost.h"
#include "features/Labels.h"
#include "lib/Mathematics.h"
#include "lib/Cplex.h"
#include "lib/DynamicArray.h"
#include "lib/Signal.h"
#include "lib/Time.h"

CLPBoost::CLPBoost() : CSparseLinearClassifier(), C1(1), C2(1), use_bias(true), epsilon(1e-3)
{
	u=NULL;
	dim=NULL;
	num_sfeat=0;
	num_svec=0;
	sfeat=NULL;
}


CLPBoost::~CLPBoost()
{
	cleanup();
}

bool CLPBoost::init(INT num_vec)
{
	u=new DREAL[num_vec];
	ASSERT(u);
	for (INT i=0; i<num_vec; i++)
		u[i]=1.0/num_vec;

	dim=new CDynamicArray<INT>(100000);

	sfeat= get_features()->get_transposed(num_sfeat, num_svec);

	if (sfeat)
		return true;
	else
		return false;
}

void CLPBoost::cleanup()
{
	delete[] u;
	u=NULL;

	get_features()->clean_tsparse(sfeat, num_svec);
	sfeat=NULL;

	delete dim;
	dim=NULL;
}

DREAL CLPBoost::find_max_violator(INT& max_dim)
{
	DREAL max_val=0;
	max_dim=-1;

	for (INT i=0; i<num_svec; i++)
	{
		DREAL valplus=0;
		DREAL valminus=0;

		for (INT j=0; j<sfeat[i].num_feat_entries; j++)
		{
			INT idx=sfeat[i].features[j].feat_index;
			DREAL v=u[idx]*get_labels()->get_label(idx)*sfeat[i].features[j].entry;
			valplus+=v;
			valminus-=v;
		}

		if (valplus>max_val || max_dim==-1)
		{
			max_dim=i;
			max_val=valplus;
		}

		if (valminus>max_val)
		{
			max_dim=num_svec+i;
			max_val=valminus;
		}
	}

	dim->append_element(max_dim);
	return max_val;
}

bool CLPBoost::train()
{
	ASSERT(get_labels());
	ASSERT(get_features());
	INT num_train_labels=get_labels()->get_num_labels();
	INT num_feat=features->get_num_features();
	INT num_vec=features->get_num_vectors();

	ASSERT(num_vec==num_train_labels);
	delete[] w;
	w=new DREAL[num_feat];
	memset(w,0,sizeof(DREAL)*num_feat);
	w_dim=num_feat;
	ASSERT(w);

	CCplex solver;
	solver.init(E_LINEAR);
	SG_PRINT("setting up lpboost\n");
	solver.setup_lpboost(C1, num_vec);
	SG_PRINT("finished setting up lpboost\n");

	DREAL result = init(num_vec);

	ASSERT(result);

	INT num_hypothesis=0;
	CTime time;

	while (!(CSignal::cancel_computations()))
	{
		INT max_dim=0;
		DREAL violator=find_max_violator(max_dim);
		SG_PRINT("iteration:%06d violator: %10.17f (>1.0) chosen: %d\n", num_hypothesis, violator, max_dim);
		if (violator <= 1.0+epsilon && num_hypothesis>1) //no constraint violated
		{
			SG_PRINT("converged after %d iterations!\n", num_hypothesis);
			break;
		}

		DREAL factor=+1.0;
		if (max_dim>=num_svec)
		{
			factor=-1.0;
			max_dim-=num_svec;
		}

		TSparseEntry<DREAL>* h=sfeat[max_dim].features;
		INT len=sfeat[max_dim].num_feat_entries;
		solver.add_lpboost_constraint(factor, h, len, num_vec, get_labels());
		solver.optimize(u);
		//CMath::display_vector(u, num_vec, "u");
		num_hypothesis++;

		if (get_max_train_time()>0 && time.cur_time_diff()>get_max_train_time())
			break;
	}
	DREAL* lambda=new DREAL[num_hypothesis];
	solver.optimize(u, lambda);

	//CMath::display_vector(lambda, num_hypothesis, "lambda");
	for (INT i=0; i<num_hypothesis; i++)
	{
		INT d=dim->get_element(i);
		if (d>=num_svec)
			w[d-num_svec]+=lambda[i];
		else
			w[d]-=lambda[i];

	}
	//solver.write_problem("problem.lp");
	solver.cleanup();

	cleanup();
	
	return true;
}
#endif