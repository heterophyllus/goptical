#include <goptical/core/curve/curve_asphere.hpp>
#include <goptical/core/curve/sphere.hpp>
#include <goptical/core/math/vector.hpp>
#include <goptical/core/math/vector_pair.hpp>

#include <memory>
#include <cstdio>

struct Data
{
  double r, k, A4, A6, A8, A10, A12, A14;
  double x0, y0, z0, l, m, n;
  double x, y, z;
};

static Data data[] = {
  { 27.1969999999999992, -0.8120099999999999, 0.0000050791000000, -0.0000000062026200, 0.0000000000115776, -0.0000000000000204, 0.0000000000000000, 0.0000000000000000, -0.7919553695491796, 1.3717069373861661, -0.0104958012912375, -0.0054028043922186, 0.0093579317106790, 0.9999416177051526, -0.7922614771556935, 1.3722371313132316, 0.0461580608567707 },
  { -131.7249999999999943, 1.0000000000000000, 0.0000033868600000, -0.0000000010397500, 0.0000000000514761, 0.0000000000000118, -0.0000000000000001, 0.0000000000000000, 8.7998449921814927, -11.4681812708805300, -3.0848614357286088, 0.1141624886684117, -0.1487794518593705, 0.9822584185872169, 9.0918761969783848, -11.8487637466332263, -0.5722137810766454 },
  { -131.7249999999999943, 1.0000000000000000, 0.0000033868600000, -0.0000000010397500, 0.0000000000514761, 0.0000000000000118, -0.0000000000000001, 0.0000000000000000, -0.8918474513468104, -1.5447250983334908, -5.3163256081579142, -0.0107812026246427, -0.0186735907125761, 0.9997675043128107, -0.9490301644423303, -1.6437684627295657, -0.0136316182804969 },
  { -280.3879999999999768, 1.0000000000000000, -0.0000145264000000, -0.0000000274974000, 0.0000000000408509, -0.0000000000001220, 0.0000000000000022, -0.0000000000000000, 12.8333017166290162, 9.8473387520461646, -5.1259113097132616, -0.2004776043349571, -0.1538318762915804, 0.9675455978902099, 12.0336094856274833, 9.2337133211215843, -1.2664343355183014 },
  { -280.3879999999999768, 1.0000000000000000, -0.0000145264000000, -0.0000000274974000, 0.0000000000408509, -0.0000000000001220, 0.0000000000000022, -0.0000000000000000, -0.9821625744758037, 1.7011554802847451, -0.2171115884804671, 0.0153003424976701, -0.0265009705791699, 0.9995316893814914, -0.9789470677904168, 1.6955860593335776, -0.0070508770975919 },
  { -55.5020000000000024, 2.6129400000000000, -0.0000048694800000, -0.0000000236249000, 0.0000000000719463, -0.0000000000003121, 0.0000000000000021, -0.0000000000000000, 7.5840163988027234, -13.1359017281618513, -4.9764343355182366, -0.0251888843784106, 0.0436284275293852, 0.9987302340547646, 7.5204256577421464, -13.0257593337539763, -2.4550842531152375 },
  { 27.1969999999999992, -0.8120099999999999, 0.0000050791000000, -0.0000000062026200, 0.0000000000115776, -0.0000000000000204, 0.0000000000000000, 0.0000000000000000, 0.0000000000000000, -4.2197825271319198, 0.2314620187626910, 0.0000000000000000, -0.0291191999274085, 0.9995759461869754, 0.0000000000000000, -4.2225887211664581, 0.3277903541651389 },
  { -131.7249999999999943, 1.0000000000000000, 0.0000033868600000, -0.0000000010397500, 0.0000000000514761, 0.0000000000000118, -0.0000000000000001, 0.0000000000000000, 0.0000000000000000, 7.3833702810561714, -4.7696525394957723, 0.0000000000000000, 0.0923575160012259, 0.9957259106993664, 0.0000000000000000, 7.8055155235774203, -0.2184154095225562 },
  { -280.3879999999999768, 1.0000000000000000, -0.0000145264000000, -0.0000000274974000, 0.0000000000408509, -0.0000000000001220, 0.0000000000000022, -0.0000000000000000, 0.0000000000000000, 11.3250390132565482, -2.4717964528745355, 0.0000000000000000, -0.1812964257096363, 0.9834284956339783, 0.0000000000000000, 10.9541524196165589, -0.4599506958139296 },
};

int
do_test2 ()
{
  for (int i = 0; i < 9; i++)
    {
      Data *d = &data[i];
      auto surface
	= std::make_shared<goptical::curve::Asphere> (d->r, d->k, d->A4, d->A6,
						      d->A8, d->A10, d->A12,
						      d->A14);
      Vector3 origin (d->x0, d->y0, d->z0);
      Vector3 pos_dir (d->l, d->m, d->n);
      VectorPair3 ray (origin, pos_dir);
      Vector3 point (0, 0, 0);
      if (surface->intersect (point, ray))
	{
	  printf ("Got      %.16f, %.16f, %.16f\n", point.x (), point.y (),
		  point.z ());
	  printf ("Expected %.16f, %.16f, %.16f\n", d->x, d->y, d->z);
	}
    }
  return 0;
}

int
do_test1 ()
{
  auto surface
    = std::make_shared<goptical::curve::Asphere> (1.0 / 0.25284872, 1.0, -0.005,
						  0.00001, -0.0000005, 0, 0, 0, false);

  //  auto surface = std::make_shared<goptical::curve::Sphere> (1.0 /
  //  0.25284872);
  Vector3 pos_dir (0.0, 0.1736, 0.98481625);
  Vector3 origin (1.48, 0.0, 0.0);
  VectorPair3 ray (origin, pos_dir);
  Vector3 point (0, 0, 0);
  surface->intersect (point, ray);
  printf ("%.16f, %.16f, %.16f\n", point.x (), point.y (), point.z ());

  // Vector3 pos_dir2 (0.98481625, 0.1736, 0.0);
  // Vector3 origin2 (0, 0.0, 1.48);
  Vector3 point2 (0, 0, 0);
  Vector3 normal2 (0, 0, 0);
  goptical::curve::compute_intersection (origin, pos_dir, surface.get (),
					 point2, normal2);
  printf ("%.16f, %.16f, %.16f\n", point2.x (), point2.y (), point2.z ());

  return 0;
}

int
main (int argc, const char *argv[])
{
  do_test1 ();
  do_test2 ();
}