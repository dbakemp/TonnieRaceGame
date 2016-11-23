#include "Box2DUtils.h"
#include "SDL2_gfxPrimitives.h"

void Box2DUtils::DrawBody(SDL_Renderer* buffer, b2Body* body, CCamera* camera, int fr, int fg, int fb, int falpha, int lr, int lg, int lb, int lalpha, bool aa)
{
	const b2Transform& xf = body->GetTransform();
	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		switch (f->GetType())
		{
		case b2Shape::e_circle:
			{
				b2CircleShape* circle = static_cast<b2CircleShape*>(f->GetShape());

				b2Vec2 center = b2Mul(xf, circle->m_p);
				float32 radius = circle->m_radius;
				//b2Vec2 axis = xf.R.col1;
				b2Vec2 axis = xf.q.GetXAxis();

				//m_debugDraw->DrawSolidCircle(center, radius, axis, color);
				if (falpha > 0)
				{
					filledCircleRGBA(buffer, center.x + camera->posX, center.y + camera->posY, static_cast<int>(radius), fr, fg, fb, falpha);
				}
				if (lalpha > 0)
				{
					if (aa)
					{
						aacircleRGBA(buffer, center.x + camera->posX, center.y + camera->posY, static_cast<int>(radius), lr, lg, lb, lalpha);
					}
					else
					{
						aacircleRGBA(buffer, center.x + camera->posX, center.y + camera->posY, static_cast<int>(radius), lr, lg, lb, lalpha);
					}
				}
				else if (aa)
				{
					aacircleRGBA(buffer, center.x + camera->posX, center.y + camera->posY, static_cast<int>(radius), fr, fg, fb, falpha);
				}
			}
			break;

		case b2Shape::e_polygon:
			{
				b2PolygonShape* poly = static_cast<b2PolygonShape*>(f->GetShape());
				//int32 vertexCount = poly->m_vertexCount;
				int32 vertexCount = poly->GetVertexCount();
				b2Assert(vertexCount <= b2_maxPolygonVertices);
				b2Vec2 vertices[b2_maxPolygonVertices];
				Sint16 xv[b2_maxPolygonVertices];
				Sint16 yv[b2_maxPolygonVertices];
				for (int32 i = 0; i < vertexCount; ++i)
				{
					vertices[i] = b2Mul(xf, poly->m_vertices[i]);
					xv[i] = static_cast<int>((vertices[i].x * 5) - camera->posX);
					yv[i] = static_cast<int>((vertices[i].y * 5) - camera->posY);
				}
				if (falpha > 0)
				{
					filledPolygonRGBA(buffer, xv, yv, static_cast<Sint16>(vertexCount), fr, fg, fb, falpha);
				}
				if (lalpha > 0)
				{
					if (aa)
					{
						aapolygonRGBA(buffer, xv, yv, static_cast<Sint16>(vertexCount), lr, lg, lb, lalpha);
					}
					else
					{
						polygonRGBA(buffer, xv, yv, static_cast<Sint16>(vertexCount), lr, lg, lb, lalpha);
					}
				}
				else if (aa)
				{
					aapolygonRGBA(buffer, xv, yv, static_cast<Sint16>(vertexCount), fr, fg, fb, falpha);
				}
				//m_debugDraw->DrawSolidPolygon(vertices, vertexCount, color);
			}
			break;
		case b2Shape::e_edge: break;
		case b2Shape::e_chain: break;
		case b2Shape::e_typeCount: break;
		default: break;
		}
	}
}
