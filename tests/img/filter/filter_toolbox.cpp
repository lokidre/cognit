/**************************************************************************
 *   COGNIT - Computer Vision and Recognition Library                     *
 *   Copyright (C) 1996-2025 Andrei Mirzoyan                              * 
 *                                                                        *
 *   This Source Code Form is subject to the terms of the Mozilla Public  *
 *   License, v. 2.0. If a copy of the MPL was not distributed with this  *
 *   file, You can obtain one at http://mozilla.org/MPL/2.0/.             *
 **************************************************************************/
#include <filter_toolbox.h>

#include <filter.h>

extern t_filter_config<filter_float_type> filter_config ;
extern t_filter_handler<filter_float_type> filter_data[100] ;
extern t_filter<filter_float_type> filter ;


tFilterToolbox::tFilterToolbox ( void )
{
  // user interface
  #include <filter_toolbox.ccs>

  ui.LoadqT(_ccs_filter_toolbox,this) ;


  //
  // window position and stuff
  //
  //tRect ParentRect ;
  //ParentWidget->GetRect ( &ParentRect ) ;
  //Move ( ParentRect.x+ParentRect.w, ParentRect.y ) ;

  ExStyle |= WS_EX_TOOLWINDOW ;
  //Style = WS_CHILD | WS_OVERLAPPEDWINDOW ;

  //
  // setup controls
  //
  try {
    FilterListCtl = (tComboBoxCtl *)ui.GetWidget("FilterListCtl") ;

    ParamNameCtl[0] = (tLabelCtl *)ui.GetWidget("ParamName1") ;
    ParamNameCtl[1] = (tLabelCtl *)ui.GetWidget("ParamName2") ;
    ParamNameCtl[2] = (tLabelCtl *)ui.GetWidget("ParamName3") ;
    ParamNameCtl[3] = (tLabelCtl *)ui.GetWidget("ParamName4") ;

    ParamValueCtl[0] = (tEditCtl *)ui.GetWidget("ParamValue1") ;
    ParamValueCtl[1] = (tEditCtl *)ui.GetWidget("ParamValue2") ;
    ParamValueCtl[2] = (tEditCtl *)ui.GetWidget("ParamValue3") ;
    ParamValueCtl[3] = (tEditCtl *)ui.GetWidget("ParamValue4") ;

    PassesCtl = (tEditCtl *)ui.GetWidget("PassesEdit") ;
  }
  catch(...) {
    InternalError() ;
  }
}

bool tFilterToolbox::Create ( tWidget *ParentWidget )
{

  {
    // signals
    SignalConnect ( FilterListCtl, signal_item_select, this, SIGNAL_SLOT2(SlotFilterSelect) ) ;
    SignalConnect ( ui.GetWidget("ProcessButton"), signal_button_press, this, SIGNAL_SLOT2(SlotProcess) ) ;
    SignalConnect ( ui.GetWidget("OriginButton"), signal_button_press, this, SIGNAL_SLOT2(SlotOrigin) ) ;
    SignalConnect ( ui.GetWidget("SetOriginButton"), signal_button_press, this, SIGNAL_SLOT2(SlotSetOrigin) ) ;
  }

  //
  // fillup controls
  //
  PassesCtl->SetInt ( filter_config.passes ) ;

  for ( int i = 0 ; filter_data[i].filter_name ; i++ ) {
    FilterListCtl->InsertItem(filter_data[i].filter_name) ;
  }

  CurrentFilter = filter_config.current_filter ;

  if ( !tWindowCtl::Create(ParentWidget) )
    return false ;

  {
    tRect r ;
    GetRect ( &r ) ;

    FilterPostToolbox.Move ( r.x, r.y+r.h ) ;
    FilterPostToolbox.Create(this) ;
  }


  UpdateCurrentFilterControls() ;

  return true ;
}


void tFilterToolbox::UpdateCurrentFilterControls ( void )
{
  FilterListCtl->SetCurSel(CurrentFilter) ;

  for ( int i = 0 ; i < MAX_FILTER_PARAMS ; i++ ) {
    if ( filter_data[CurrentFilter].param[i].param_name ) {
      std::string s = filter_data[CurrentFilter].param[i].param_name ;
      s += ":" ;
      ParamNameCtl[i]->SetText ( s ) ;
      ParamValueCtl[i]->SetFloat ( filter_data[CurrentFilter].param[i].param_value ) ;

      ParamNameCtl[i]->SetVisible() ;
      ParamValueCtl[i]->SetVisible() ;
    } else {
      ParamNameCtl[i]->SetVisible(false) ;
      ParamValueCtl[i]->SetVisible(false) ;
    }
  }

  FilterPostToolbox.AbsoluteCheck->SetCheck(filter_data[CurrentFilter].absolute) ;
  FilterPostToolbox.ThresholdCheck->SetCheck(filter_data[CurrentFilter].threshold) ;
  FilterPostToolbox.ThresholdMinEdit->SetFloat(filter_data[CurrentFilter].threshold_min) ;
  FilterPostToolbox.ThresholdMaxEdit->SetFloat(filter_data[CurrentFilter].threshold_max) ;
  FilterPostToolbox.NormOfGradientCheck->SetCheck(filter_data[CurrentFilter].norm_of_gradient) ;
  FilterPostToolbox.NonMaximaCheck->SetCheck(filter_data[CurrentFilter].non_maxima_suppression ) ;
  FilterPostToolbox.ZeroCrossingCheck->SetCheck(filter_data[CurrentFilter].zero_crossing) ;
}

void tFilterToolbox::ReadCurrentFilterControls ( void )
{
  for ( int i = 0 ; i < MAX_FILTER_PARAMS ; i++ ) {
    if ( filter_data[CurrentFilter].param[i].param_name )
      filter_data[CurrentFilter].param[i].param_value = ParamValueCtl[i]->GetFloat() ;
  }

  filter_data[CurrentFilter].absolute = FilterPostToolbox.AbsoluteCheck->GetCheck() ;
  filter_data[CurrentFilter].threshold = FilterPostToolbox.ThresholdCheck->GetCheck() ;
  filter_data[CurrentFilter].threshold_min = FilterPostToolbox.ThresholdMinEdit->GetFloat() ;
  filter_data[CurrentFilter].threshold_max = FilterPostToolbox.ThresholdMaxEdit->GetFloat() ;
  filter_data[CurrentFilter].norm_of_gradient = FilterPostToolbox.NormOfGradientCheck->GetCheck() ;
  filter_data[CurrentFilter].non_maxima_suppression = FilterPostToolbox.NonMaximaCheck->GetCheck() ;
  filter_data[CurrentFilter].zero_crossing = FilterPostToolbox.ZeroCrossingCheck->GetCheck() ;
}


void tFilterToolbox::SlotFilterSelect ( void )
{
  int NewFilter = FilterListCtl->GetCurSel() ;
  if ( NewFilter != CurrentFilter ) {
    ReadCurrentFilterControls() ;
    CurrentFilter = NewFilter ;
    UpdateCurrentFilterControls() ;
  }
}


void tFilterToolbox::SlotProcess ( void )
{
  filter_config.passes = PassesCtl->GetInt() ;
  filter_config.current_filter = CurrentFilter ;
  ReadCurrentFilterControls() ;
  SignalEmit ( "filter_process" ) ;
}

void tFilterToolbox::SlotOrigin ( void )
{
  SignalEmit ( "filter_origin" ) ;
}

void tFilterToolbox::SlotSetOrigin ( void )
{
  SignalEmit ( "filter_set_origin" ) ;
}


