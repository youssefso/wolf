using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemydumbAI : MonoBehaviour {

	// Use this for initialization
	public float speed = 1;
	public float rotSpeed = 1f;
	private Transform target;
	private Transform gun;
	public int maxHealth = 100;
	public int currentHealth;
	void Start () {
		currentHealth = maxHealth;
		target = GameObject.FindWithTag("Player").GetComponent<Transform>();
		gun = transform.Find("Weapon").GetComponent<Transform>();
	}
	
	// Update is called once per frame
	void Update ()
	{
		if (Vector2.Distance(transform.position, target.position) > 4)
			transform.position = Vector2.MoveTowards(transform.position, target.position, speed * Time.deltaTime);
		else
			transform.position = Vector2.MoveTowards(transform.position, target.position, -speed * Time.deltaTime);
		///cannon rotation
		Vector2 direction = target.position - transform.position;
		Quaternion rot = Quaternion.LookRotation(Vector3.forward,direction);
		gun.rotation = Quaternion.Slerp(gun.transform.rotation, rot, rotSpeed * Time.deltaTime);
	}

	public void TakeDamage(int damageAmount)
	{
		Debug.Log(currentHealth);
		currentHealth  -= damageAmount;
		if (currentHealth <= 0)
			Destroy(gameObject);
	}
}
