#include <stdlib.h>

#include <gtk/gtk.h>

#include "gtkplt.h"
#include "axis.h"
#include "plotarea.h"
#include "graphs.h"
#include "margins.h"

GtkPltPlotData *gtkplt_init_plot() {
   GtkPltPlotData *plotdata_ptr = (GtkPltPlotData*) malloc(sizeof(GtkPltPlotData));
   plotdata_ptr->Axis = gtkplt_axis_init();
   plotdata_ptr->PlotArea = gtkplt_plotarea_init();
   double default_margin = 5;
   plotdata_ptr->left_margin = default_margin;
   plotdata_ptr->right_margin = default_margin;
   plotdata_ptr->top_margin = default_margin;
   plotdata_ptr->bottom_margin = default_margin;
   plotdata_ptr->title = NULL;
   plotdata_ptr->titlefont = NULL;
   plotdata_ptr->titlefontsize = 0;
   plotdata_ptr->title_height = 12;
   plotdata_ptr->title_margin = 4;

   return plotdata_ptr;
}

void gtkplt_finalize_plot(GtkPltPlotData *plotdata_ptr) {
   gtkplt_axis_finalize(plotdata_ptr->Axis);
   plotdata_ptr->Axis = NULL;
   gtkplt_plotarea_finalize(plotdata_ptr->PlotArea);
   plotdata_ptr->PlotArea = NULL;
   free(plotdata_ptr);
}

void gtkplt_plot_margins_debug(cairo_t *cr, GtkPltPlotData *data) {
   // outer margins
   cairo_set_source_rgb(cr, 163.0/255.0, 73.0/255.0, 164.0/255.0);
   cairo_set_line_width(cr, 0);
   cairo_rectangle(cr,
                   gtkplt_otmargin_xmin(data),
                   gtkplt_otmargin_ymin(data),
                   gtkplt_otmargin_xmax(data)-gtkplt_otmargin_xmin(data),
                   gtkplt_otmargin_ymax(data)-gtkplt_otmargin_ymin(data));
   cairo_rectangle(cr,
                   gtkplt_obmargin_xmin(data),
                   gtkplt_obmargin_ymin(data),
                   gtkplt_obmargin_xmax(data)-gtkplt_obmargin_xmin(data),
                   gtkplt_obmargin_ymax(data)-gtkplt_obmargin_ymin(data));
   cairo_rectangle(cr,
                   gtkplt_olmargin_xmin(data),
                   gtkplt_olmargin_ymin(data),
                   gtkplt_olmargin_xmax(data)-gtkplt_olmargin_xmin(data),
                   gtkplt_olmargin_ymax(data)-gtkplt_olmargin_ymin(data));
   cairo_rectangle(cr,
                   gtkplt_ormargin_xmin(data),
                   gtkplt_ormargin_ymin(data),
                   gtkplt_ormargin_xmax(data)-gtkplt_ormargin_xmin(data),
                   gtkplt_ormargin_ymax(data)-gtkplt_ormargin_ymin(data));
   cairo_stroke_preserve(cr);
   cairo_fill(cr);

   // Title space
   cairo_set_source_rgb(cr, 0.0/255.0, 64.0/255.0, 128.0/255.0);
   cairo_rectangle(cr,
                   gtkplt_ttmargin_xmin(data),
                   gtkplt_ttmargin_ymin(data),
                   gtkplt_ttmargin_xmax(data)-gtkplt_ttmargin_xmin(data),
                   gtkplt_ttmargin_ymax(data)-gtkplt_ttmargin_ymin(data));
   cairo_rectangle(cr,
                   gtkplt_tbmargin_xmin(data),
                   gtkplt_tbmargin_ymin(data),
                   gtkplt_tbmargin_xmax(data)-gtkplt_tbmargin_xmin(data),
                   gtkplt_tbmargin_ymax(data)-gtkplt_tbmargin_ymin(data));
   cairo_stroke_preserve(cr);
   cairo_fill(cr);

   // Axis label space
   cairo_set_source_rgb(cr, 0.0/255.0, 200.0/255.0, 0.0/255.0);
   cairo_rectangle(cr,
                   gtkplt_xaxis_area_xmin(data),
                   gtkplt_xaxis_area_ymin(data),
                   gtkplt_xaxis_area_xmax(data)-gtkplt_xaxis_area_xmin(data),
                   gtkplt_xaxis_area_ymax(data)-gtkplt_xaxis_area_ymin(data));
   cairo_rectangle(cr,
                   gtkplt_yaxis_area_xmin(data),
                   gtkplt_yaxis_area_ymin(data),
                   gtkplt_yaxis_area_xmax(data)-gtkplt_yaxis_area_xmin(data),
                   gtkplt_yaxis_area_ymax(data)-gtkplt_yaxis_area_ymin(data));
   cairo_stroke_preserve(cr);
   cairo_fill(cr);

//   // Axis dist space
//   cairo_set_source_rgb(cr, 0.0/255.0, 0.0/255.0, 200.0/255.0);
//   cairo_rectangle(cr,
//                   data->left_margin,
//                   data->top_margin+2*data->title_margin+data->title_height,
//                   data->left_margin+data->Axis[0].axis_width,
//                   height-data->top_margin-2*data->title_margin-data->title_height-data->Axis[1].axis_width-data->Axis[1].axis_label_dist-data->bottom_margin);
//   cairo_rectangle(cr,
//                   data->left_margin+data->Axis[0].axis_width+data->Axis[0].axis_label_dist,
//                   height-data->bottom_margin-data->Axis[1].axis_width,
//                   data->left_margin+data->Axis[0].axis_width,
//                   data->Axis[1].axis_width);
//   cairo_stroke_preserve(cr);
//   cairo_fill(cr);



}

void gtkplt_plot(cairo_t *cr, GtkPltPlotData *data) {

   // set background to white
   cairo_set_source_rgba(cr,
                         1.0,
                         1.0,
                         1.0,
                         1.0);
   cairo_paint(cr);

   // DEBUG margin plotter
#ifdef _DEBUG
   gtkplt_plot_margins_debug(cr, data);
#endif

   // draw title

   // draw axis

   // draw graphs
   // TODO: correct upper bound
   for (int i=0; i<1; i++) {
      if (data->PlotArea->graphs[i].valid) {
         gtkplt_plot_graph(cr,
                           data,
                           data->PlotArea->graphs+i);
      }
   }

   // draw legend
   
   // draw labels

}
