#ifndef _SFSROSD_H_
#define _SFSROSD_H_

#include <sfsro_prot_cfs.h>
#include "sfsmisc.h"
#include "arpc.h"
#include "crypt.h"
#include <sfsdb.h>
#include "vec.h"


extern sfs_connectres cres;
extern sfs_fsinfo fsinfores;
extern sfsrodb db;

class sfsroclient {
  ptr<axprt_stream> x;
  ptr<asrv> rosrv;
  ptr<asrv> sfssrv;

  ref<bool> destroyed;

  bool unixauth;
  uid_t uid;

  bool authid_valid;
  sfs_hash authid;


  void dispatch (ref<bool> b, svccb *sbp);
  void getdata_cb(svccb *sbp, sfsro_datares *res, ref<bool> d);
  void remote_get_data(sfs_hash fh,
			     struct in_addr *pub_addr, 
			     short pub_port,
			     sfsro_datares *res,
			     callback<void, sfsro_datares *>::ref cb);


  void remoteget_cb(sfs_hash fh,
		    callback<void, sfsro_datares *>::ref cb,
		    sfsro_datares *res,
		    int fd);
  void remotegetdata_cb_call(sfs_hash fh, 
			     callback<void, sfsro_datares *>::ref cb,
			     sfsro_datares *res,
			     clnt_stat err); 
  void proxygetdata_cb(svccb *sbp, sfsro_datares *res, ref<bool> d);
  void proxygetdata_cb_call(svccb *sbp, sfsro_datares *res);
  void partialproxygetdata_cb(svccb *sbp, sfsro_datares *res, ref<bool> d);
  void partialproxygetdata_cb_call(svccb *sbp, sfsro_datares *res);

public:
  sfsroclient (ptr<axprt_stream> x, const authunix_parms *aup = NULL);
  ~sfsroclient ();
};

#endif _SFSROSD_H_
