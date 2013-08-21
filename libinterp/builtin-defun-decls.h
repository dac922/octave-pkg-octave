// DO NOT EDIT!  Generated automatically by mkbuiltins.

#if !defined (octave_builtin_defun_decls_h)
#define octave_builtin_defun_decls_h 1

#include "oct-obj.h"

#define DEFUN_DECL(name) \
  extern OCTINTERP_API octave_value_list \
  name (const octave_value_list& = octave_value_list (), int = 0);

DEFUN_DECL (F__version_info__);
DEFUN_DECL (Fisguirunning);
DEFUN_DECL (Fargv);
DEFUN_DECL (Fprogram_invocation_name);
DEFUN_DECL (Fprogram_name);
DEFUN_DECL (Fsparse_auto_mutate);
DEFUN_DECL (Flogical);
DEFUN_DECL (Fiscell);
DEFUN_DECL (Fcell);
DEFUN_DECL (Fiscellstr);
DEFUN_DECL (Fcellstr);
DEFUN_DECL (Fstruct2cell);
DEFUN_DECL (Fclass);
DEFUN_DECL (F__isa_parent__);
DEFUN_DECL (F__parent_classes__);
DEFUN_DECL (Fisobject);
DEFUN_DECL (Fismethod);
DEFUN_DECL (F__methods__);
DEFUN_DECL (Fsuperiorto);
DEFUN_DECL (Finferiorto);
DEFUN_DECL (Ffunctions);
DEFUN_DECL (Ffunc2str);
DEFUN_DECL (Fstr2func);
DEFUN_DECL (Fis_function_handle);
DEFUN_DECL (Finline);
DEFUN_DECL (Fformula);
DEFUN_DECL (Fargnames);
DEFUN_DECL (Fvectorize);
DEFUN_DECL (Fsingle);
DEFUN_DECL (F__java_init__);
DEFUN_DECL (F__java_exit__);
DEFUN_DECL (FjavaObject);
DEFUN_DECL (FjavaMethod);
DEFUN_DECL (F__java_get__);
DEFUN_DECL (F__java_set__);
DEFUN_DECL (Fjava2mat);
DEFUN_DECL (Fjava_matrix_autoconversion);
DEFUN_DECL (Fjava_unsigned_autoconversion);
DEFUN_DECL (Fdebug_java);
DEFUN_DECL (Fisjava);
DEFUN_DECL (Fisnull);
DEFUN_DECL (FonCleanup);
DEFUN_DECL (Fallow_noninteger_range_as_index);
DEFUN_DECL (Fdouble);
DEFUN_DECL (Fstruct);
DEFUN_DECL (Fisstruct);
DEFUN_DECL (F__fieldnames__);
DEFUN_DECL (Fisfield);
DEFUN_DECL (Fnfields);
DEFUN_DECL (Fcell2struct);
DEFUN_DECL (Frmfield);
DEFUN_DECL (Fstruct_levels_to_print);
DEFUN_DECL (Fprint_struct_array_contents);
DEFUN_DECL (Ftypeinfo);
DEFUN_DECL (Fnargin);
DEFUN_DECL (Fnargout);
DEFUN_DECL (Foptimize_subsasgn_calls);
DEFUN_DECL (Fisargout);
DEFUN_DECL (Fsizeof);
DEFUN_DECL (Fsubsref);
DEFUN_DECL (Fsubsasgn);
DEFUN_DECL (Fis_sq_string);
DEFUN_DECL (Fis_dq_string);
DEFUN_DECL (Fint16);
DEFUN_DECL (Fint32);
DEFUN_DECL (Fint64);
DEFUN_DECL (Fint8);
DEFUN_DECL (Fuint16);
DEFUN_DECL (Fuint32);
DEFUN_DECL (Fuint64);
DEFUN_DECL (Fuint8);
DEFUN_DECL (F__end__);
DEFUN_DECL (Fdo_braindead_shortcircuit_evaluation);
DEFUN_DECL (Fmax_recursion_depth);
DEFUN_DECL (Fsilent_functions);
DEFUN_DECL (Fstring_fill_char);
DEFUN_DECL (Fiskeyword);
DEFUN_DECL (F__display_tokens__);
DEFUN_DECL (F__token_count__);
DEFUN_DECL (F__lexer_debug_flag__);
DEFUN_DECL (F__contourc__);
DEFUN_DECL (F__dispatch__);
DEFUN_DECL (F__lin_interpn__);
DEFUN_DECL (F__pchip_deriv__);
DEFUN_DECL (F__qp__);
DEFUN_DECL (Fbalance);
DEFUN_DECL (Fbesselj);
DEFUN_DECL (Fbessely);
DEFUN_DECL (Fbesseli);
DEFUN_DECL (Fbesselk);
DEFUN_DECL (Fbesselh);
DEFUN_DECL (Fairy);
DEFUN_DECL (Fbetainc);
DEFUN_DECL (Fbetaincinv);
DEFUN_DECL (Fbitand);
DEFUN_DECL (Fbitor);
DEFUN_DECL (Fbitxor);
DEFUN_DECL (Fbitshift);
DEFUN_DECL (Fbitmax);
DEFUN_DECL (Fintmax);
DEFUN_DECL (Fintmin);
DEFUN_DECL (Fsizemax);
DEFUN_DECL (Fbsxfun);
DEFUN_DECL (Fcellfun);
DEFUN_DECL (Farrayfun);
DEFUN_DECL (Fnum2cell);
DEFUN_DECL (Fmat2cell);
DEFUN_DECL (Fcellslices);
DEFUN_DECL (Fcellindexmat);
DEFUN_DECL (Fcolloc);
DEFUN_DECL (Fconv2);
DEFUN_DECL (Fconvn);
DEFUN_DECL (Fdaspk_options);
DEFUN_DECL (Fdaspk);
DEFUN_DECL (Fdasrt_options);
DEFUN_DECL (Fdasrt);
DEFUN_DECL (Fdassl_options);
DEFUN_DECL (Fdassl);
DEFUN_DECL (Fall);
DEFUN_DECL (Fany);
DEFUN_DECL (Fatan2);
DEFUN_DECL (Fhypot);
DEFUN_DECL (Flog2);
DEFUN_DECL (Frem);
DEFUN_DECL (Fmod);
DEFUN_DECL (Fcumprod);
DEFUN_DECL (Fcumsum);
DEFUN_DECL (Fdiag);
DEFUN_DECL (Fprod);
DEFUN_DECL (Fhorzcat);
DEFUN_DECL (Fvertcat);
DEFUN_DECL (Fcat);
DEFUN_DECL (Fpermute);
DEFUN_DECL (Fipermute);
DEFUN_DECL (Flength);
DEFUN_DECL (Fndims);
DEFUN_DECL (Fnumel);
DEFUN_DECL (Fsize);
DEFUN_DECL (Fsize_equal);
DEFUN_DECL (Fnnz);
DEFUN_DECL (Fnzmax);
DEFUN_DECL (Frows);
DEFUN_DECL (Fcolumns);
DEFUN_DECL (Fsum);
DEFUN_DECL (Fsumsq);
DEFUN_DECL (Fislogical);
DEFUN_DECL (Fisinteger);
DEFUN_DECL (Fiscomplex);
DEFUN_DECL (Fisfloat);
DEFUN_DECL (Fcomplex);
DEFUN_DECL (Fisreal);
DEFUN_DECL (Fisempty);
DEFUN_DECL (Fisnumeric);
DEFUN_DECL (Fismatrix);
DEFUN_DECL (Fones);
DEFUN_DECL (Fzeros);
DEFUN_DECL (FInf);
DEFUN_DECL (FNaN);
DEFUN_DECL (Fe);
DEFUN_DECL (Feps);
DEFUN_DECL (Fpi);
DEFUN_DECL (Frealmax);
DEFUN_DECL (Frealmin);
DEFUN_DECL (FI);
DEFUN_DECL (FNA);
DEFUN_DECL (Ffalse);
DEFUN_DECL (Ftrue);
DEFUN_DECL (Feye);
DEFUN_DECL (Flinspace);
DEFUN_DECL (Fresize);
DEFUN_DECL (Freshape);
DEFUN_DECL (Fvec);
DEFUN_DECL (Fsqueeze);
DEFUN_DECL (Ffull);
DEFUN_DECL (Fnorm);
DEFUN_DECL (Fnot);
DEFUN_DECL (Fuplus);
DEFUN_DECL (Fuminus);
DEFUN_DECL (Ftranspose);
DEFUN_DECL (Fctranspose);
DEFUN_DECL (Fplus);
DEFUN_DECL (Fminus);
DEFUN_DECL (Fmtimes);
DEFUN_DECL (Fmrdivide);
DEFUN_DECL (Fmpower);
DEFUN_DECL (Fmldivide);
DEFUN_DECL (Flt);
DEFUN_DECL (Fle);
DEFUN_DECL (Feq);
DEFUN_DECL (Fge);
DEFUN_DECL (Fgt);
DEFUN_DECL (Fne);
DEFUN_DECL (Ftimes);
DEFUN_DECL (Frdivide);
DEFUN_DECL (Fpower);
DEFUN_DECL (Fldivide);
DEFUN_DECL (Fand);
DEFUN_DECL (For);
DEFUN_DECL (Ftic);
DEFUN_DECL (Ftoc);
DEFUN_DECL (Fcputime);
DEFUN_DECL (Fsort);
DEFUN_DECL (F__sort_rows_idx__);
DEFUN_DECL (Fissorted);
DEFUN_DECL (Fnth_element);
DEFUN_DECL (F__accumarray_sum__);
DEFUN_DECL (F__accumarray_min__);
DEFUN_DECL (F__accumarray_max__);
DEFUN_DECL (F__accumdim_sum__);
DEFUN_DECL (Fmerge);
DEFUN_DECL (Fdiff);
DEFUN_DECL (Frepelems);
DEFUN_DECL (Fbase64_encode);
DEFUN_DECL (Fbase64_decode);
DEFUN_DECL (Fdbstop);
DEFUN_DECL (Fdbclear);
DEFUN_DECL (Fdbstatus);
DEFUN_DECL (Fdbwhere);
DEFUN_DECL (Fdbtype);
DEFUN_DECL (Fdblist);
DEFUN_DECL (Fdbstack);
DEFUN_DECL (Fdbup);
DEFUN_DECL (Fdbdown);
DEFUN_DECL (Fdbstep);
DEFUN_DECL (Fdbcont);
DEFUN_DECL (Fdbquit);
DEFUN_DECL (Fisdebugmode);
DEFUN_DECL (FEDITOR);
DEFUN_DECL (FEXEC_PATH);
DEFUN_DECL (FIMAGE_PATH);
DEFUN_DECL (FOCTAVE_HOME);
DEFUN_DECL (FOCTAVE_VERSION);
DEFUN_DECL (Fdet);
DEFUN_DECL (Fcd);
DEFUN_DECL (Fpwd);
DEFUN_DECL (Freaddir);
DEFUN_DECL (Fmkdir);
DEFUN_DECL (Frmdir);
DEFUN_DECL (Flink);
DEFUN_DECL (Fsymlink);
DEFUN_DECL (Freadlink);
DEFUN_DECL (Frename);
DEFUN_DECL (Fglob);
DEFUN_DECL (Ffnmatch);
DEFUN_DECL (Ffilesep);
DEFUN_DECL (Fpathsep);
DEFUN_DECL (Fconfirm_recursive_rmdir);
DEFUN_DECL (Fdlmread);
DEFUN_DECL (Fdot);
DEFUN_DECL (Fblkmm);
DEFUN_DECL (Feig);
DEFUN_DECL (Fellipj);
DEFUN_DECL (Frethrow);
DEFUN_DECL (Ferror);
DEFUN_DECL (Fwarning);
DEFUN_DECL (Flasterror);
DEFUN_DECL (Flasterr);
DEFUN_DECL (Flastwarn);
DEFUN_DECL (Fusage);
DEFUN_DECL (Fbeep_on_error);
DEFUN_DECL (Fdebug_on_error);
DEFUN_DECL (Fdebug_on_warning);
DEFUN_DECL (Ffft);
DEFUN_DECL (Fifft);
DEFUN_DECL (Ffft2);
DEFUN_DECL (Fifft2);
DEFUN_DECL (Ffftn);
DEFUN_DECL (Fifftn);
DEFUN_DECL (Ffclose);
DEFUN_DECL (Ffclear);
DEFUN_DECL (Ffflush);
DEFUN_DECL (Ffgetl);
DEFUN_DECL (Ffgets);
DEFUN_DECL (Ffskipl);
DEFUN_DECL (Ffopen);
DEFUN_DECL (Ffreport);
DEFUN_DECL (Ffrewind);
DEFUN_DECL (Ffseek);
DEFUN_DECL (Fftell);
DEFUN_DECL (Ffprintf);
DEFUN_DECL (Fprintf);
DEFUN_DECL (Ffputs);
DEFUN_DECL (Fputs);
DEFUN_DECL (Fsprintf);
DEFUN_DECL (Ffscanf);
DEFUN_DECL (Fsscanf);
DEFUN_DECL (Fscanf);
DEFUN_DECL (Ffread);
DEFUN_DECL (Ffwrite);
DEFUN_DECL (Ffeof);
DEFUN_DECL (Fferror);
DEFUN_DECL (Fpopen);
DEFUN_DECL (Fpclose);
DEFUN_DECL (Ftmpnam);
DEFUN_DECL (Ftmpfile);
DEFUN_DECL (Fmkstemp);
DEFUN_DECL (Fumask);
DEFUN_DECL (FP_tmpdir);
DEFUN_DECL (FSEEK_SET);
DEFUN_DECL (FSEEK_CUR);
DEFUN_DECL (FSEEK_END);
DEFUN_DECL (Fstdin);
DEFUN_DECL (Fstdout);
DEFUN_DECL (Fstderr);
DEFUN_DECL (Ffilter);
DEFUN_DECL (Ffind);
DEFUN_DECL (Fgammainc);
DEFUN_DECL (Fgcd);
DEFUN_DECL (Fgetgrent);
DEFUN_DECL (Fgetgrgid);
DEFUN_DECL (Fgetgrnam);
DEFUN_DECL (Fsetgrent);
DEFUN_DECL (Fendgrent);
DEFUN_DECL (Fgetpwent);
DEFUN_DECL (Fgetpwuid);
DEFUN_DECL (Fgetpwnam);
DEFUN_DECL (Fsetpwent);
DEFUN_DECL (Fendpwent);
DEFUN_DECL (Fgetrusage);
DEFUN_DECL (Fgivens);
DEFUN_DECL (Fishandle);
DEFUN_DECL (F__is_handle_visible__);
DEFUN_DECL (Freset);
DEFUN_DECL (Fset);
DEFUN_DECL (Fget);
DEFUN_DECL (F__get__);
DEFUN_DECL (F__go_figure__);
DEFUN_DECL (F__calc_dimensions__);
DEFUN_DECL (F__go_axes__);
DEFUN_DECL (F__go_line__);
DEFUN_DECL (F__go_text__);
DEFUN_DECL (F__go_image__);
DEFUN_DECL (F__go_surface__);
DEFUN_DECL (F__go_patch__);
DEFUN_DECL (F__go_hggroup__);
DEFUN_DECL (F__go_uimenu__);
DEFUN_DECL (F__go_uicontrol__);
DEFUN_DECL (F__go_uipanel__);
DEFUN_DECL (F__go_uicontextmenu__);
DEFUN_DECL (F__go_uitoolbar__);
DEFUN_DECL (F__go_uipushtool__);
DEFUN_DECL (F__go_uitoggletool__);
DEFUN_DECL (F__go_delete__);
DEFUN_DECL (F__go_axes_init__);
DEFUN_DECL (F__go_handles__);
DEFUN_DECL (F__go_figure_handles__);
DEFUN_DECL (F__go_execute_callback__);
DEFUN_DECL (F__image_pixel_size__);
DEFUN_DECL (Favailable_graphics_toolkits);
DEFUN_DECL (Fregister_graphics_toolkit);
DEFUN_DECL (Floaded_graphics_toolkits);
DEFUN_DECL (Fdrawnow);
DEFUN_DECL (Faddlistener);
DEFUN_DECL (Fdellistener);
DEFUN_DECL (Faddproperty);
DEFUN_DECL (Fwaitfor);
DEFUN_DECL (Fbuilt_in_docstrings_file);
DEFUN_DECL (Fget_help_text);
DEFUN_DECL (Fget_help_text_from_file);
DEFUN_DECL (F__operators__);
DEFUN_DECL (F__keywords__);
DEFUN_DECL (F__builtins__);
DEFUN_DECL (F__which__);
DEFUN_DECL (F__list_functions__);
DEFUN_DECL (Fdoc_cache_file);
DEFUN_DECL (Ftexi_macros_file);
DEFUN_DECL (Finfo_file);
DEFUN_DECL (Finfo_program);
DEFUN_DECL (Fmakeinfo_program);
DEFUN_DECL (Fsuppress_verbose_help_message);
DEFUN_DECL (Fhess);
DEFUN_DECL (Fhex2num);
DEFUN_DECL (Fnum2hex);
DEFUN_DECL (Finput);
DEFUN_DECL (Fyes_or_no);
DEFUN_DECL (Fkeyboard);
DEFUN_DECL (Fecho);
DEFUN_DECL (Fcompletion_matches);
DEFUN_DECL (Freadline_read_init_file);
DEFUN_DECL (Freadline_re_read_init_file);
DEFUN_DECL (Fadd_input_event_hook);
DEFUN_DECL (Fremove_input_event_hook);
DEFUN_DECL (FPS1);
DEFUN_DECL (FPS2);
DEFUN_DECL (FPS4);
DEFUN_DECL (Fcompletion_append_char);
DEFUN_DECL (Fecho_executing_commands);
DEFUN_DECL (F__request_drawnow__);
DEFUN_DECL (F__gud_mode__);
DEFUN_DECL (Ffilemarker);
DEFUN_DECL (Finv);
DEFUN_DECL (Finverse);
DEFUN_DECL (Fkron);
DEFUN_DECL (Fgenpath);
DEFUN_DECL (Frehash);
DEFUN_DECL (Fcommand_line_path);
DEFUN_DECL (Frestoredefaultpath);
DEFUN_DECL (F__pathorig__);
DEFUN_DECL (Fpath);
DEFUN_DECL (Faddpath);
DEFUN_DECL (Frmpath);
DEFUN_DECL (Fload);
DEFUN_DECL (Fsave);
DEFUN_DECL (Fcrash_dumps_octave_core);
DEFUN_DECL (Fsave_default_options);
DEFUN_DECL (Foctave_core_file_limit);
DEFUN_DECL (Foctave_core_file_name);
DEFUN_DECL (Foctave_core_file_options);
DEFUN_DECL (Fsave_header_format_string);
DEFUN_DECL (Flookup);
DEFUN_DECL (Fsave_precision);
DEFUN_DECL (Flsode_options);
DEFUN_DECL (Flsode);
DEFUN_DECL (Flu);
DEFUN_DECL (Fluupdate);
DEFUN_DECL (Fluinc);
DEFUN_DECL (Fabs);
DEFUN_DECL (Facos);
DEFUN_DECL (Facosh);
DEFUN_DECL (Fangle);
DEFUN_DECL (Farg);
DEFUN_DECL (Fasin);
DEFUN_DECL (Fasinh);
DEFUN_DECL (Fatan);
DEFUN_DECL (Fatanh);
DEFUN_DECL (Fcbrt);
DEFUN_DECL (Fceil);
DEFUN_DECL (Fconj);
DEFUN_DECL (Fcos);
DEFUN_DECL (Fcosh);
DEFUN_DECL (Ferf);
DEFUN_DECL (Ferfinv);
DEFUN_DECL (Ferfcinv);
DEFUN_DECL (Ferfc);
DEFUN_DECL (Ferfcx);
DEFUN_DECL (Ferfi);
DEFUN_DECL (Fdawson);
DEFUN_DECL (Fexp);
DEFUN_DECL (Fexpm1);
DEFUN_DECL (Fisfinite);
DEFUN_DECL (Ffix);
DEFUN_DECL (Ffloor);
DEFUN_DECL (Fgamma);
DEFUN_DECL (Fimag);
DEFUN_DECL (Fisalnum);
DEFUN_DECL (Fisalpha);
DEFUN_DECL (Fisascii);
DEFUN_DECL (Fiscntrl);
DEFUN_DECL (Fisdigit);
DEFUN_DECL (Fisinf);
DEFUN_DECL (Fisgraph);
DEFUN_DECL (Fislower);
DEFUN_DECL (Fisna);
DEFUN_DECL (Fisnan);
DEFUN_DECL (Fisprint);
DEFUN_DECL (Fispunct);
DEFUN_DECL (Fisspace);
DEFUN_DECL (Fisupper);
DEFUN_DECL (Fisxdigit);
DEFUN_DECL (Flgamma);
DEFUN_DECL (Flog);
DEFUN_DECL (Flog10);
DEFUN_DECL (Flog1p);
DEFUN_DECL (Freal);
DEFUN_DECL (Fround);
DEFUN_DECL (Froundb);
DEFUN_DECL (Fsign);
DEFUN_DECL (Fsignbit);
DEFUN_DECL (Fsin);
DEFUN_DECL (Fsinh);
DEFUN_DECL (Fsqrt);
DEFUN_DECL (Ftan);
DEFUN_DECL (Ftanh);
DEFUN_DECL (Ftoascii);
DEFUN_DECL (Ftolower);
DEFUN_DECL (Ftoupper);
DEFUN_DECL (Fmatrix_type);
DEFUN_DECL (Fmin);
DEFUN_DECL (Fmax);
DEFUN_DECL (Fcummin);
DEFUN_DECL (Fcummax);
DEFUN_DECL (Fmd5sum);
DEFUN_DECL (Fmgorth);
DEFUN_DECL (Fnproc);
DEFUN_DECL (Fedit_history);
DEFUN_DECL (Fhistory);
DEFUN_DECL (Frun_history);
DEFUN_DECL (Fhistory_control);
DEFUN_DECL (Fhistory_size);
DEFUN_DECL (Fhistory_file);
DEFUN_DECL (Fhistory_timestamp_format_string);
DEFUN_DECL (Fhistory_save);
DEFUN_DECL (F__octave_link_enabled__);
DEFUN_DECL (F__octave_link_edit_file__);
DEFUN_DECL (F__octave_link_message_dialog__);
DEFUN_DECL (F__octave_link_question_dialog__);
DEFUN_DECL (F__octave_link_file_dialog__);
DEFUN_DECL (F__octave_link_list_dialog__);
DEFUN_DECL (F__octave_link_input_dialog__);
DEFUN_DECL (F__octave_link_show_preferences__);
DEFUN_DECL (F__octave_link_show_doc__);
DEFUN_DECL (Fdiary);
DEFUN_DECL (Fmore);
DEFUN_DECL (Fterminal_size);
DEFUN_DECL (Fpage_output_immediately);
DEFUN_DECL (Fpage_screen_output);
DEFUN_DECL (FPAGER);
DEFUN_DECL (FPAGER_FLAGS);
DEFUN_DECL (Fpinv);
DEFUN_DECL (Frats);
DEFUN_DECL (Fdisp);
DEFUN_DECL (Ffdisp);
DEFUN_DECL (Fformat);
DEFUN_DECL (Ffixed_point_format);
DEFUN_DECL (Fprint_empty_dimensions);
DEFUN_DECL (Fsplit_long_rows);
DEFUN_DECL (Foutput_max_field_width);
DEFUN_DECL (Foutput_precision);
DEFUN_DECL (F__profiler_enable__);
DEFUN_DECL (F__profiler_reset__);
DEFUN_DECL (F__profiler_data__);
DEFUN_DECL (Fquad_options);
DEFUN_DECL (Fquad);
DEFUN_DECL (Fquadcc);
DEFUN_DECL (Fqz);
DEFUN_DECL (Frand);
DEFUN_DECL (Frandn);
DEFUN_DECL (Frande);
DEFUN_DECL (Frandg);
DEFUN_DECL (Frandp);
DEFUN_DECL (Frandperm);
DEFUN_DECL (Frcond);
DEFUN_DECL (Fregexp);
DEFUN_DECL (Fregexpi);
DEFUN_DECL (Fregexprep);
DEFUN_DECL (Fschur);
DEFUN_DECL (Frsf2csf);
DEFUN_DECL (FSIG);
DEFUN_DECL (Fdebug_on_interrupt);
DEFUN_DECL (Fsighup_dumps_octave_core);
DEFUN_DECL (Fsigterm_dumps_octave_core);
DEFUN_DECL (Fissparse);
DEFUN_DECL (Fsparse);
DEFUN_DECL (Fspalloc);
DEFUN_DECL (Fspparms);
DEFUN_DECL (Fsqrtm);
DEFUN_DECL (Fstr2double);
DEFUN_DECL (Fstrfind);
DEFUN_DECL (Fstrrep);
DEFUN_DECL (Fchar);
DEFUN_DECL (Fstrvcat);
DEFUN_DECL (Fischar);
DEFUN_DECL (Fstrcmp);
DEFUN_DECL (Fstrncmp);
DEFUN_DECL (Fstrcmpi);
DEFUN_DECL (Fstrncmpi);
DEFUN_DECL (Flist_in_columns);
DEFUN_DECL (Fsub2ind);
DEFUN_DECL (Find2sub);
DEFUN_DECL (Fsvd);
DEFUN_DECL (Fsvd_driver);
DEFUN_DECL (Fsyl);
DEFUN_DECL (Fignore_function_time_stamp);
DEFUN_DECL (F__current_scope__);
DEFUN_DECL (F__dump_symtab_info__);
DEFUN_DECL (Fdup2);
DEFUN_DECL (Fexec);
DEFUN_DECL (Fpopen2);
DEFUN_DECL (Ffcntl);
DEFUN_DECL (Ffork);
DEFUN_DECL (Fgetpgrp);
DEFUN_DECL (Fgetpid);
DEFUN_DECL (Fgetppid);
DEFUN_DECL (Fgetegid);
DEFUN_DECL (Fgetgid);
DEFUN_DECL (Fgeteuid);
DEFUN_DECL (Fgetuid);
DEFUN_DECL (Fkill);
DEFUN_DECL (Flstat);
DEFUN_DECL (Fmkfifo);
DEFUN_DECL (Fpipe);
DEFUN_DECL (Fstat);
DEFUN_DECL (FS_ISREG);
DEFUN_DECL (FS_ISDIR);
DEFUN_DECL (FS_ISCHR);
DEFUN_DECL (FS_ISBLK);
DEFUN_DECL (FS_ISFIFO);
DEFUN_DECL (FS_ISLNK);
DEFUN_DECL (FS_ISSOCK);
DEFUN_DECL (Fgethostname);
DEFUN_DECL (Funame);
DEFUN_DECL (Funlink);
DEFUN_DECL (Fwaitpid);
DEFUN_DECL (FWIFEXITED);
DEFUN_DECL (FWEXITSTATUS);
DEFUN_DECL (FWIFSIGNALED);
DEFUN_DECL (FWTERMSIG);
DEFUN_DECL (FWCOREDUMP);
DEFUN_DECL (FWIFSTOPPED);
DEFUN_DECL (FWSTOPSIG);
DEFUN_DECL (FWIFCONTINUED);
DEFUN_DECL (Fcanonicalize_file_name);
DEFUN_DECL (FF_DUPFD);
DEFUN_DECL (FF_GETFD);
DEFUN_DECL (FF_GETFL);
DEFUN_DECL (FF_SETFD);
DEFUN_DECL (FF_SETFL);
DEFUN_DECL (FO_APPEND);
DEFUN_DECL (FO_ASYNC);
DEFUN_DECL (FO_CREAT);
DEFUN_DECL (FO_EXCL);
DEFUN_DECL (FO_NONBLOCK);
DEFUN_DECL (FO_RDONLY);
DEFUN_DECL (FO_RDWR);
DEFUN_DECL (FO_SYNC);
DEFUN_DECL (FO_TRUNC);
DEFUN_DECL (FO_WRONLY);
DEFUN_DECL (FWNOHANG);
DEFUN_DECL (FWUNTRACED);
DEFUN_DECL (FWCONTINUE);
DEFUN_DECL (Fclc);
DEFUN_DECL (Fgetenv);
DEFUN_DECL (Fputenv);
DEFUN_DECL (Fkbhit);
DEFUN_DECL (Fpause);
DEFUN_DECL (Fsleep);
DEFUN_DECL (Fusleep);
DEFUN_DECL (Fisieee);
DEFUN_DECL (Fnative_float_format);
DEFUN_DECL (Ftilde_expand);
DEFUN_DECL (Ftime);
DEFUN_DECL (Fgmtime);
DEFUN_DECL (Flocaltime);
DEFUN_DECL (Fmktime);
DEFUN_DECL (Fstrftime);
DEFUN_DECL (Fstrptime);
DEFUN_DECL (Fquit);
DEFUN_DECL (Fwarranty);
DEFUN_DECL (Fsystem);
DEFUN_DECL (Fatexit);
DEFUN_DECL (Foctave_config_info);
DEFUN_DECL (Ftril);
DEFUN_DECL (Ftriu);
DEFUN_DECL (Ftypecast);
DEFUN_DECL (Fbitpack);
DEFUN_DECL (Fbitunpack);
DEFUN_DECL (Fisvarname);
DEFUN_DECL (Ffile_in_loadpath);
DEFUN_DECL (Ffile_in_path);
DEFUN_DECL (Fdo_string_escapes);
DEFUN_DECL (Fundo_string_escapes);
DEFUN_DECL (Fis_absolute_filename);
DEFUN_DECL (Fis_rooted_relative_filename);
DEFUN_DECL (Fmake_absolute_filename);
DEFUN_DECL (Ffind_dir_in_path);
DEFUN_DECL (Ferrno);
DEFUN_DECL (Ferrno_list);
DEFUN_DECL (Fisindex);
DEFUN_DECL (Fisglobal);
DEFUN_DECL (Fexist);
DEFUN_DECL (Fwho);
DEFUN_DECL (Fwhos);
DEFUN_DECL (Fmlock);
DEFUN_DECL (Fmunlock);
DEFUN_DECL (Fmislocked);
DEFUN_DECL (Fclear);
DEFUN_DECL (Fwhos_line_format);
DEFUN_DECL (Fmissing_function_hook);
DEFUN_DECL (F__varval__);
DEFUN_DECL (Fdebug_jit);
DEFUN_DECL (Fjit_enable);
DEFUN_DECL (Fjit_startcnt);
DEFUN_DECL (Fautoload);
DEFUN_DECL (Fmfilename);
DEFUN_DECL (Fsource);
DEFUN_DECL (Ffeval);
DEFUN_DECL (Fbuiltin);
DEFUN_DECL (Feval);
DEFUN_DECL (Fassignin);
DEFUN_DECL (Fevalin);
DEFUN_DECL (F__parser_debug_flag__);

#undef DEFUN_DECL

#endif

