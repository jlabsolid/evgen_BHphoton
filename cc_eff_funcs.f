C----------------------------------------------------------------------
C-   Purpose and Methods : crossing of the stright line(R0,d)
C-                         with a plane
C-
C-   Inputs  :   r0(3) - initial point of line
C-               dir(3) - vector direction: r = R0 + s*D
C-               plane_par(3) - array of plane parameters:
C-      plane_par(1)*x + plane_par(2)*y + plane_par(3)*z + 1 = 0
C-
C-   Outputs :   cc_vcrpl =  0 - no cross with the plane.
C-                           1 - cross in positive direction
C-                          -1 - cross in negative direction
C-               dist    =  Distance to the cross point
C-               cross_point(3) =  Cross point coordinates.
C-
C-   Created    23-NOV-1998   Alexander V. Vlassov
C----------------------------------------------------------------------
      subroutine get_vcrpl(nnt, r0, dir, plane_par, dist, cross_point)
C       implicit double precision (a-h,o-z)
      real a,b,c,un,vsmall,t
C       real r0(3), dir(3), plane_par(3),x(3),d(3),cross_point(3)     
      dimension r0(3), dir(3), plane_par(3),x(3),d(3),cross_point(3)
      Integer nnt
      un = 1.0000000000
      vsmall = 0.000001

      a = 0.
      b = 0.
      c = 0.
      dist = 0.
      do i=1,3
         c = c+un*dir(i)*dir(i)
      enddo
      c = sqrt(c)
      if(c.le.vsmall) then
         nnt =0
         return
      endif
      do i=1,3
         d(i) = un*dir(i)/c
      enddo
      do i=1,3
         a = a+un*plane_par(i)*d(i)
         b = b+un*plane_par(i)*r0(i)
      enddo
      b = b+un;

      if(abs(b).le.vsmall) then
         do i=1,3
            cross_point(i) = r0(i)
         enddo
         nnt = 1
      else if(abs(a).le.vsmall) then
         do i=1,3
            cross_point(i) = 0
         enddo
         nnt = 0
      else
         t = -b/a
         do i=1,3
            cross_point(i) = t*dir(i) + r0(i)
         enddo
         nnt = 1
         dist = t
         if(t.lt.0) then
            dist = -t
            nnt = -1
         endif
      endif

      return
      end





C  *********************************************
C  SUBROUTINE CC_coord_BINconv
C  INPUTS :
C          CCTheta = theta on CC plane
C          CCPhi = phi on CC plane
C  OUTPUT :
C          it = theta bin
C          ip = phi bin
C  *********************************************
       subroutine CC_coord_BINconv(CCTheta,CCPhi,it,ip)
c      implicit double precision (a-h,o-z)
       REAL CCTheta,CCPhi
       Integer ip,it
       it = 1+(1+INT((CCTheta-5.)/40.*200.))
       ip = 1+(1+INT((CCPhi+25.)/50.*200.))
       if(it.gt.200)it=200
       if(ip.gt.200)ip=200
       if(it.lt.1)it=1
       if(ip.lt.1)ip=1
       return
       end


C  *********************************************
       subroutine CC_coordCCconv(point,dir,CCTheta,CCPhi)
C$$$      implicit double precision (a-h,o-z)
       REAL CCTheta,CCPhi
       REAL dist
       Integer nnt
       REAL tconv,r,s
c      dimension point(3), dir(3), x(3), cc_pln(3)
       REAL point(3),dir(3)
       dimension cc_pln(3),x(3)
       data cc_pln(1),cc_pln(2),cc_pln(3)
     &     /-0.0007840784063,0.,-0.001681461571/
       tconv = 180./acos(-1.)
       call get_vcrpl(nnt,point,dir,cc_pln,dist,x)

       CCTheta = -999.
       CCPhi = -999.
       if(nnt.ne.0) then
        r = sqrt(x(1)*x(1) + x(2)*x(2) + x(3)*x(3))
        s = sqrt(x(1)*x(1) + x(2)*x(2))
        CCTheta = tconv*acos(x(3)/r)
        CCPhi = tconv*atan2(x(2)/s,x(1)/s)
       endif
  
       return
       end
C  *********************************************
