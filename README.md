# SDL2-Mr-Shooter

<h1>Collisions</h1>

<p>Each element has its own collider. I've used SDL_Rect to implement the collision logic in this game. First, I'll explain the hero's collider. There is nothing particularly special about the hero's box collider, but it's essential to understand some of the interactions that colliders produce.</p>
<div align="center">
  <img src="https://github.com/ImNotMenduina/SDL2-Mr-Shooter/assets/100011745/6333fb65-fd34-4602-8619-d31a596e1a64">
</div>

<h2>Hero Collider</h2>
<p>The hero entity has two types of colliders. The first one is very simple to understand; it's just a rectangle that encompasses all the hero sprites. The second collider is also a rectangle, but it only covers half of the hero. I used this second one to monitor interactions between the hero's feet and the platform tiles.</p>
<div align="center">
  <img src="https://github.com/ImNotMenduina/SDL2-Mr-Shooter/assets/100011745/e5245074-3087-4c39-a668-63878ce39694">
</div>

<h2>Enemy Collider</h2>
<p>The enemy entity has four types of colliders. However, it now employs two distinct types of colliders, with two of them being identical to those of the hero.</p>
<div align="center">
  <img src="https://github.com/ImNotMenduina/SDL2-Mr-Shooter/assets/100011745/6333fb65-fd34-4602-8619-d31a596e1a64">
</div>

<h3>Enemy Range #1</h3>
 <p> The first collider is utilized to detect if the hero is in proximity to the enemy object. If this condition holds true, the enemy will commence firing at the hero.</p>
<div align="center">
  <img src="https://github.com/ImNotMenduina/SDL2-Mr-Shooter/assets/100011745/5c41fe6d-2272-45d6-bc7a-f08341002b8a">
</div>
<h3>Enemy Range #2</h3>
 <p> On the other hand, I've employed the second collider to identify situations where the hero is in very close proximity to the enemy object. Thus, if this condition is met, the enemy will advance toward the hero's x position. As is typical in platform games, if the enemy comes into contact with the hero, the hero loses a life, and this scenario is no exception.</p>
 <div align="center">
   <img src="https://github.com/ImNotMenduina/SDL2-Mr-Shooter/assets/100011745/c00457d6-7610-4b49-b16b-a0d85993c4b2">
 </div>

 <h1>Bullets and Enemies allocation</h1>
 <p>This is the most important topic of the README. What I mean is how to determine the best data structure to store all the enemies and bullets. I've chosen Lists for this purpose. However, this isn't the most challenging part. Here, I've employed two different logics.</p>
<p>1. When the hero is shooting, some bullets are created somewhere in the heap. However, when a bullet collides with an object or goes out of the visible screen, we need to free the chunk of memory that the bullet is occupying.</p>
<p>2. When an enemy dies, we also need to release the corresponding memory chunk, following the same logic as with bullets.</p>
<p>That's why I've created 'free()' functions for both situations. Here's an example:</p>

<pre>
<h2>(Free)Bullets Code:</h2>
      
void freeBullet(LISTBullets* lst)
{
 	if (lst->begin == NULL)
		exit(0); // can't free an empty list.

	_ONE_BULLET* aux = lst->begin;
	_ONE_BULLET* check = NULL;

	while (aux != NULL)
	{
		check = aux;
		aux = aux->next;

		if (check->bullet->getLife() < 1) // If the life of this bullet reaches zero, then we can deallocate that memory
		{
			if (check == lst->begin)
			{
				lst->begin = aux;
			}
			else if (check->next == NULL)
			{
				check->prev->next = NULL;
			}
			else
			{
				check->prev->next = check->next;
				check->next>prev = check->prev;
			}
			free(check);
			lst->size--;
		}
	}
}
</pre>
