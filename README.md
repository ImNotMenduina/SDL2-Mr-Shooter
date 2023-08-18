# SDL2-Mr-Shooter

<h1>Collisions</h1>

<p>Each element has its own collider. I've used SDL_Rect to implement the collision logic in this game. First, I'll explain the hero's collider. There is nothing particularly special about the hero's box collider, but it's essential to understand some of the interactions that colliders produce.</p>

<h2>Hero Collider</h2>
<p>The hero entity has two types of colliders. The first one is very simple to understand; it's just a rectangle that encompasses all the hero sprites. The second collider is also a rectangle, but it only covers half of the hero. I used this second one to monitor interactions between the hero's feet and the platform tiles.</p>
<div align="center">
  <img src="https://github.com/ImNotMenduina/SDL2-Mr-Shooter/assets/100011745/e5245074-3087-4c39-a668-63878ce39694">
</div>

<h2>Enemy Collider</h2>
<p>The enemy entity has four types of colliders. However, it now employs two distinct types of colliders, with two of them being identical to those of the hero.</p>
<div align="center">
  <img src="https://github.com/ImNotMenduina/SDL2-Mr-Shooter/assets/100011745/2139c692-bebf-4b1d-a16b-996d39cf2c85">
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
