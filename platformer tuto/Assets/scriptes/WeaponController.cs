using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class WeaponController : MonoBehaviour {

	public GameObject bullet;
	public Transform firePosition;
	public float shootforce = 20f;
	void Update () {
		if (Input.GetButtonDown("Fire1"))
			Shoot();
	}
	void Shoot()
	{
		GameObject bull = Instantiate(bullet, firePosition.position, transform.rotation);
		bull.GetComponent<Rigidbody2D>().AddForce(transform.up * shootforce);
		GameObject player;
		player = GameObject.Find("player");
		Physics2D.IgnoreCollision(player.GetComponent<Collider2D>(), bull.GetComponent<Collider2D>());
	}
}
