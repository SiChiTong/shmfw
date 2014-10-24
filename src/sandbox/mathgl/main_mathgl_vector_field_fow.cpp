
#include <mgl2/qt.h>
void mgls_prepare2v(HMDT a, HMDT b)
{
  register long i,j,n=20,m=30;
  if(a) mgl_data_create(a,n,m,1);
  if(b) mgl_data_create(b,n,m,1);
  mreal x,y;
  for(i=0;i<n;i++)  for(j=0;j<m;j++)
  {
    x=i/(n-1.); y=j/(m-1.);
    if(a) mgl_data_set_value(a, 0.6*sin(2*M_PI*x)*sin(3*M_PI*y)+0.4*cos(3*M_PI*x*y), i,j,0);
    if(b) mgl_data_set_value(b, 0.6*cos(2*M_PI*x)*cos(3*M_PI*y)+0.4*cos(3*M_PI*x*y), i,j,0);
  }
}
void mgls_prepare3v(HMDT ex, HMDT ey, HMDT ez)
{
  register long i,j,k,n=10;
  if(!ex || !ey || !ez) return;
  mgl_data_create(ex,n,n,n);
  mgl_data_create(ey,n,n,n);
  mgl_data_create(ez,n,n,n);
  mreal x,y,z, r1,r2;
  for(i=0;i<n;i++)  for(j=0;j<n;j++)  for(k=0;k<n;k++)
  {
    x=2*i/(n-1.)-1; y=2*j/(n-1.)-1; z=2*k/(n-1.)-1;
    r1 = pow(x*x+y*y+(z-0.3)*(z-0.3)+0.03,1.5);
    r2 = pow(x*x+y*y+(z+0.3)*(z+0.3)+0.03,1.5);
    mgl_data_set_value(ex, 0.2*x/r1 - 0.2*x/r2, i,j,k);
    mgl_data_set_value(ey, 0.2*y/r1 - 0.2*y/r2, i,j,k);
    mgl_data_set_value(ez, 0.2*(z-0.3)/r1 - 0.2*(z+0.3)/r2, i,j,k);
  }
}
int sample(mglGraph *gr)
{
  mglData a,b;  mgls_prepare2v(&a,&b);
  gr->SubPlot(2,2,0,""); gr->Title("Flow plot (default)");
  gr->Box();  gr->Flow(a,b);

  gr->SubPlot(2,2,1,"");  gr->Title("'v' style");
  gr->Box();  gr->Flow(a,b,"v");

  gr->SubPlot(2,2,2,"");  gr->Title("'\\#' style");
  gr->Box();  gr->Flow(a,b,"#");

  mglData ex,ey,ez; mgls_prepare3v(&ex,&ey,&ez);
  gr->SubPlot(2,2,3); gr->Title("3d variant");  gr->Rotate(50,60);
  gr->Box();  gr->Flow(ex,ey,ez);
  return 0;
}

//-----------------------------------------------------
int main ( int argc,char **argv ) {
    mglQT gr ( sample,"MathGL examples" );
    return gr.Run();
}
